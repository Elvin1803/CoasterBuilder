'''
Script to convert custom .obj file format to .cbdat file format.

The custom .obj file format supports:
  - Mesh parenting: Specified by "p" prefix when parsing an object.
  - Mesh custom origin: Specified by "ori" prefix when parsing an object.

The custom .obj file format does NOT support:
  - Not triangulated faces
  - Multiple materials per object
'''

from PIL import Image
import os
import struct
import sys


workingDir = ''


class mesh:
    def __init__(self, name):
        self.name = name
        self.vertexAttribs = [] # 3 floats (Position), 3 floats (Normals), 2 floats (TexCoords)
        self.indices = []
        self.parent = ""
        self.origin = [0, 0, 0]
        self.material = ""


class image:
    def __init__(self, width, height, data):
        self.width = width
        self.height = height
        self.data = data # Stored as RGBA (one pixel -> 4 bytes)


class material:
    def __init__(self, name):
        self.name = name
        self.ambiantColor = [0, 0, 0]
        self.diffuseColor = [0, 0, 0]
        self.specular = [0, 0, 0]
        self.specularExponent = 0
        self.emissiveColor = [0, 0, 0]
        self.dissolve = 0
        self.opticalDensity = 0
        self.textureKd = None # Stored as RGBA (one pixel -> 4 bytes)
        # FIXME: implement other material properties ?


meshes = []
materials = []


def parse_material(file):
    with open(file) as f:
        for line in f:
            if line.startswith('#'):
                continue

            tokens = line.strip().split()
            if not tokens:
                continue

            prefix, values = tokens[0], tokens[1:]

            if prefix == 'newmtl':
                materials.append(material(values[0]))

            if prefix == 'Ka':
                materials[-1].ambiantColor = list(map(float, values))
            if prefix == 'Kd':
                materials[-1].diffuseColor = list(map(float, values))
            if prefix == 'Ks':
                materials[-1].specular = list(map(float, values))
            if prefix == 'Ns':
                materials[-1].specularExponent = float(values[0])
            if prefix == 'Ke':
                materials[-1].emissiveColor = list(map(float, values))
            if prefix == 'd':
                materials[-1].dissolve = float(values[0])
            if prefix == 'Ni':
                materials[-1].opticalDensity = float(values[0])
            if prefix == 'map_Kd':
                img = Image.open(values[0]).convert("RGBA")
                img = img.transpose(Image.FLIP_TOP_BOTTOM)
                width, height = img.size
                data = img.tobytes("raw", "RGBA")
                materials[-1].textureKd = image(width, height, data)



def parse_model(file):
    vertices = []
    normals = []
    texCoords = []

    with open(file) as f:
        for line in f:
            if line.startswith('#'):
                continue

            tokens = line.strip().split()
            if not tokens:
                continue

            prefix, values = tokens[0], tokens[1:]

            # Related to material
            if prefix == 'mtllib':
                parse_material(workingDir + '/' + values[0])

            # Related to geometry
            if prefix == 'o':
                vertexAttribList = []
                meshes.append(mesh(values[0]))

            if prefix == 'p': # Parent mesh
                meshes[-1].parent = values[0]

            if prefix == 'ori': # Custom mesh origin
                meshes[-1].origin = list(map(float, values))

            if prefix == 'usemtl': # Material
                meshes[-1].material = values[0]

            if prefix == 'v':
                vertices.append([float(x) - o for x, o in zip(values, meshes[-1].origin)])
            if prefix == 'vn':
                normals.append(values)
            if prefix == 'vt':
                texCoords.append(values)

            if prefix == 'f':
                for point in values:
                    for i in range(len(vertexAttribList)):
                        if vertexAttribList[i] == point:
                            meshes[-1].indices.append(i)
                            break;
                    else:
                        vertexAttribList.append(point)
                        vtn = [(int(c) - 1) for c in point.split('/')]
                        meshes[-1].vertexAttribs.append(vertices[vtn[0]] + normals[vtn[2]] + texCoords[vtn[1]])
                        meshes[-1].indices.append(len(meshes[-1].vertexAttribs) - 1)


def writeToFile(outputFile):
    content = b''
    # Materials
    # Start by writing the number of materials to parse
    content += struct.pack('i', len(materials))
    print("Number of materials: " + str(len(materials)))

    def pack_list(lst, count=3):
        if lst:
            return struct.pack(f'{count}f', *lst)
        return struct.pack(f'{count}f', *([0.0] * count))

    for m in materials:
        # nameLen > name
        # ambiant color (3 floats)
        # diffuse color (3 floats)
        # specular (1 float)
        # emissive color (3 floats)
        # dissolve (1 float)
        # optical density (1 float)
        # width, height, textureKd (one pixel = 4 bytes RGBA) (if width == 0 there is no image)

        # name
        name_bytes = m.name.encode('utf-8')
        content += struct.pack('i', len(name_bytes)) + name_bytes
        print("nameLen: " + str(len(name_bytes)))

        content += pack_list(m.ambiantColor)
        content += pack_list(m.diffuseColor)
        content += pack_list(m.specular)
        content += struct.pack('f', m.specularExponent)
        content += pack_list(m.emissiveColor)
        content += struct.pack('f', m.dissolve)
        content += struct.pack('f', m.opticalDensity)
        # textureKd
        if m.textureKd:
            content += struct.pack('i', m.textureKd.width)
            content += struct.pack('i', m.textureKd.height)
            content += m.textureKd.data
        else:
            content += struct.pack('i', 0)

    # Meshes
    # Write the number of meshes to parse
    content += struct.pack('i', len(meshes))
    print("Number of meshes: " + str(len(meshes)))
    for o in meshes:
        # nameLen > name
        # parentNameLen > parentName (parentNameLen == 0 if there's no parent)
        # origin (3 floats)
        # MaterialNameLen > materialName (materialNameLen == 0 if there's no material)
        # vertexAttributeLen > vertexAttributes (3 floats pos, 3 floats normals, 2 floats UV)
        # indicesLen > indices

        # name
        name_bytes = o.name.encode('utf-8')
        content += struct.pack('i', len(name_bytes)) + name_bytes
        print("name: " + str(name_bytes))
        print("nameLen: " + str(len(name_bytes)))
        # parentName
        parent_name_bytes = o.parent.encode('utf-8')
        content += struct.pack('i', len(parent_name_bytes)) + parent_name_bytes
        print("parentName: " + str(parent_name_bytes))
        print("parentNameLen: " + str(len(parent_name_bytes)))
        # Custom origin
        content += pack_list(o.origin)
        print("origin: " + str(o.origin))
        # materialName
        material_name_bytes = o.material.encode('utf-8')
        content += struct.pack('i', len(material_name_bytes)) + material_name_bytes
        print("materialName: " + str(material_name_bytes))
        print("materialNameLen: " + str(len(material_name_bytes)))
        # vertexAttributes
        content += struct.pack('i', len(o.vertexAttribs) * len(o.vertexAttribs[0]) * 4)
        print("vertexAttribsLen: " + str(len(o.vertexAttribs) * len(o.vertexAttribs[0]) * 4))
        for vertAttr in o.vertexAttribs:
            content += b''.join(struct.pack('f', float(f)) for f in vertAttr)
        # indices
        content += struct.pack('i', len(o.indices) * 4)
        content += b''.join(struct.pack('i', int(i)) for i in o.indices)

    with open(outputFile, "ab") as f:
        f.write(content)


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python convertor.py <file.obj> <output>")
        exit(1)

    inputFile = sys.argv[1]
    outputFile = sys.argv[2]
    workingDir = os.path.dirname(inputFile)
    parse_model(inputFile)
    writeToFile(outputFile)
