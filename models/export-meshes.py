#!/usr/bin/env python

#based on 'export-sprites.py' and 'glsprite.py' from TCHOW Rainbow; code used is released into the public domain.

#Note: Script meant to be executed from within blender, as per:
#blender --background --python export-meshes.py

#reads 'island.blend' and writes '../dist/meshes.blob' (meshes) and '../dist/scene.blob' (scene in layer 1)

import sys

import bpy
import struct

bpy.ops.wm.open_mainfile(filepath='island.blend')

#names of objects whose meshes to write (not actually the names of the meshes):
to_write = [
	'House',
	'Land',
	'Tree',
	'Water',
	'Rock',
]

#data contains vertex and normal data from the meshes:
data = b''

#strings contains the mesh names:
strings = b''

#index gives offsets into the data (and names) for each mesh:
index = b''

vertex_count = 0
for name in to_write:
	print("Writing '" + name + "'...")
	bpy.ops.object.mode_set(mode='OBJECT') #get out of edit mode (just in case)
	assert(name in bpy.data.objects)
	obj = bpy.data.objects[name]

	obj.data = obj.data.copy() #make mesh single user, just in case it is shared with another object the script needs to write later.

	#make sure object is on a visible layer:
	bpy.context.scene.layers = obj.layers
	#select the object and make it the active object:
	bpy.ops.object.select_all(action='DESELECT')
	obj.select = True
	bpy.context.scene.objects.active = obj

	#subdivide object's mesh into triangles:
	bpy.ops.object.mode_set(mode='EDIT')
	bpy.ops.mesh.select_all(action='SELECT')
	bpy.ops.mesh.quads_convert_to_tris(quad_method='BEAUTY', ngon_method='BEAUTY')
	bpy.ops.object.mode_set(mode='OBJECT')

	#compute normals (respecting face smoothing):
	mesh = obj.data
	mesh.calc_normals_split()

	#record mesh name, start position and vertex count in the index:
	name_begin = len(strings)
	strings += bytes(name, "utf8")
	name_end = len(strings)
	index += struct.pack('I', name_begin)
	index += struct.pack('I', name_end)

	index += struct.pack('I', vertex_count)
	index += struct.pack('I', len(mesh.polygons) * 3)

	#write the mesh:
	for poly in mesh.polygons:
		assert(len(poly.loop_indices) == 3)
		for i in range(0,3):
			assert(mesh.loops[poly.loop_indices[i]].vertex_index == poly.vertices[i])
			loop = mesh.loops[poly.loop_indices[i]]
			vertex = mesh.vertices[loop.vertex_index]
			for x in mesh.vertices[loop.vertex_index].co:
				data += struct.pack('f', x)
			for x in loop.normal:
				data += struct.pack('f', x)
	vertex_count += len(mesh.polygons) * 3

#check that we wrote as much data as anticipated:
assert(vertex_count * (3 * 4 + 3 * 4) == len(data))

#write the data chunk and index chunk to an output blob:
blob = open('../dist/meshes.blob', 'wb')
#first chunk: the data
blob.write(struct.pack('4s',b'v3n3')) #type
blob.write(struct.pack('I', len(data))) #length
blob.write(data)
#second chunk: the strings
blob.write(struct.pack('4s',b'str0')) #type
blob.write(struct.pack('I', len(strings))) #length
blob.write(strings)
#third chunk: the index
blob.write(struct.pack('4s',b'idx0')) #type
blob.write(struct.pack('I', len(index))) #length
blob.write(index)

print("Wrote " + str(blob.tell()) + " bytes to meshes.blob")

#---------------------------------------------------------------------
#Export scene (object positions for every object on layer one)

#(re-open file because we adjusted mesh users in the export above)
bpy.ops.wm.open_mainfile(filepath='island.blend')

#strings chunk will have names
strings = b''
#these map from the *mesh* name of our the written objects to the *object* name they are stored under:
name_begin = dict()
name_end = dict()
for name in to_write:
	mesh_name = bpy.data.objects[name].data.name
	name_begin[mesh_name] = len(strings)
	strings += bytes(name, 'utf8')
	name_end[mesh_name] = len(strings)

#scene chunk will have transforms + indices into strings for name
scene = b''
for obj in bpy.data.objects:
	if obj.layers[0] == False: continue
	if not obj.data.name in name_begin:
		print("WARNING: not writing object '" + obj.name + "' because mesh not written.")
		continue
	scene += struct.pack('I', name_begin[obj.data.name])
	scene += struct.pack('I', name_end[obj.data.name])
	transform = obj.matrix_world.decompose()
	scene += struct.pack('3f', transform[0].x, transform[0].y, transform[0].z)
	scene += struct.pack('4f', transform[1].x, transform[1].y, transform[1].z, transform[1].w)
	scene += struct.pack('3f', transform[2].x, transform[2].y, transform[2].z)

#write the strings chunk and scene chunk to an output blob:
blob = open('../dist/scene.blob', 'wb')
#first chunk: the strings
blob.write(struct.pack('4s',b'str0')) #type
blob.write(struct.pack('I', len(strings))) #length
blob.write(strings)
#second chunk: the scene
blob.write(struct.pack('4s',b'scn0')) #type
blob.write(struct.pack('I', len(scene))) #length
blob.write(scene)

print("Wrote " + str(blob.tell()) + " bytes to scene.blob")

