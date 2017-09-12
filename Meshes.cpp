#include "Meshes.hpp"

#include <glm/glm.hpp>

#include <stdexcept>
#include <fstream>
#include <iostream>
#include <vector>

void Meshes::load(std::string const &filename, Attributes const &attributes) {
	std::ifstream file(filename, std::ios::binary);

	struct ChunkHeader {
		char magic[4] = {'\0', '\0', '\0', '\0'};
		uint32_t size = 0;
	};
	static_assert(sizeof(ChunkHeader) == 8, "header is packed");

	GLuint vao = 0;
	GLuint total = 0;
	{ //read + upload data chunk:
		ChunkHeader header;
		if (!file.read(reinterpret_cast< char * >(&header), sizeof(header))) {
			throw std::runtime_error("Failed to read data chunk header");
		}
		if (std::string(header.magic,4) != "v3n3") {
			throw std::runtime_error("Unexpected magic number in data chunk");
		}

		struct v3n3 {
			glm::vec3 v;
			glm::vec3 n;
		};
		static_assert(sizeof(v3n3) == 24, "v3n3 is packed");
		if (header.size % sizeof(v3n3) != 0) {
			throw std::runtime_error("Size of v3n3 chunk not divisible by 24");
		}
		std::vector< v3n3 > data;
		data.resize(header.size / sizeof(v3n3));
		if (!file.read(reinterpret_cast< char * >(&data[0]), sizeof(v3n3) * data.size())) {
			throw std::runtime_error("Failed to read v3n3 data.");
		}
		//upload data:
		GLuint buffer = 0;
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(v3n3) * data.size(), &data[0], GL_STATIC_DRAW);

		total = data.size(); //store total for later checks on index

		//store binding:
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		if (attributes.Position != -1U) {
			glVertexAttribPointer(attributes.Position, 3, GL_FLOAT, GL_FALSE, sizeof(v3n3), (GLbyte *)0);
			glEnableVertexAttribArray(attributes.Position);
		} else {
			std::cerr << "WARNING: loading v3n3 data from '" << filename << "', but not using the Position attribute." << std::endl;
		}
		if (attributes.Normal != -1U) {
			glVertexAttribPointer(attributes.Normal, 3, GL_FLOAT, GL_FALSE, sizeof(v3n3), (GLbyte *)0 + sizeof(glm::vec3));
			glEnableVertexAttribArray(attributes.Normal);
		} else {
			std::cerr << "WARNING: loading v3n3 data from '" << filename << "', but not using the Normal attribute." << std::endl;
		}
	}

	std::vector< char > strings;
	{ //read strings chunk:
		ChunkHeader header;
		if (!file.read(reinterpret_cast< char * >(&header), sizeof(header))) {
			throw std::runtime_error("Failed to read strings chunk header");
		}
		if (std::string(header.magic,4) != "str0") {
			throw std::runtime_error("Unexpected magic number in strings chunk");
		}
		strings.resize(header.size);
		if (!file.read(&strings[0], strings.size())) {
			throw std::runtime_error("Failed to read strings chunk");
		}
	}

	{ //read index chunk, add to meshes:
		ChunkHeader header;
		if (!file.read(reinterpret_cast< char * >(&header), sizeof(header))) {
			throw std::runtime_error("Failed to read index chunk header");
		}
		if (std::string(header.magic,4) != "idx0") {
			throw std::runtime_error("Unexpected magic number in index chunk");
		}

		struct IndexEntry {
			uint32_t name_begin, name_end;
			uint32_t vertex_start, vertex_count;
		};
		static_assert(sizeof(IndexEntry) == 16, "Index entry should be packed");

		if (header.size % sizeof(IndexEntry) != 0) {
			throw std::runtime_error("Size of index chunk not divisible by 16");
		}
		std::vector< IndexEntry > index;
		index.resize(header.size / sizeof(IndexEntry));
		if (!file.read(reinterpret_cast< char * >(&index[0]), sizeof(IndexEntry) * index.size())) {
			throw std::runtime_error("Failed to read index chunk.");
		}

		for (auto const &entry : index) {
			if (!(entry.name_begin <= entry.name_end && entry.name_end <= strings.size())) {
				throw std::runtime_error("index entry has out-of-range name begin/end");
			}
			if (!(entry.vertex_start < entry.vertex_start + entry.vertex_count && entry.vertex_start + entry.vertex_count <= total)) {
				throw std::runtime_error("index entry has out-of-range vertex start/count");
			}
			std::string name(&strings[0] + entry.name_begin, &strings[0] + entry.name_end);
			Mesh mesh;
			mesh.vao = vao;
			mesh.start = entry.vertex_start;
			mesh.count = entry.vertex_count;
			bool inserted = meshes.insert(std::make_pair(name, mesh)).second;
			if (!inserted) {
				std::cerr << "WARNING: mesh name '" + name + "' in filename '" + filename + "' collides with existing mesh." << std::endl;
			}
		}
	}

	if (file.peek() != EOF) {
		std::cerr << "WARNING: trailing data in mesh file '" + filename + "'" << std::endl;
	}
}

Mesh const &Meshes::get(std::string const &name) const {
	auto f = meshes.find(name);
	if (f == meshes.end()) {
		throw std::runtime_error("Looking up mesh that doesn't exist.");
	}
	return f->second;
}
