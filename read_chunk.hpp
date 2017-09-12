#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cassert>

template< typename T >
void read_chunk(std::istream &from, std::string const &magic, std::vector< T > *_to) {
	assert(_to);
	auto &to = *_to;

	struct ChunkHeader {
		char magic[4] = {'\0', '\0', '\0', '\0'};
		uint32_t size = 0;
	};
	static_assert(sizeof(ChunkHeader) == 8, "header is packed");

	ChunkHeader header;
	if (!from.read(reinterpret_cast< char * >(&header), sizeof(header))) {
		throw std::runtime_error("Failed to read chunk header");
	}
	if (std::string(header.magic,4) != magic) {
		throw std::runtime_error("Unexpected magic number in chunk");
	}

	if (header.size % sizeof(T) != 0) {
		throw std::runtime_error("Size of chunk not divisible by element size");
	}

	to.resize(header.size / sizeof(T));
	if (!from.read(reinterpret_cast< char * >(&to[0]), to.size() * sizeof(T))) {
		throw std::runtime_error("Failed to read chunk data.");
	}
}
