import sys
import struct

class mesh:
        def __init__(self, name):
            self.name = name
            self.vertexAttribs = [] # 3 floats (Position), 3 floats (Normals), 2 floats (TexCoords)
            self.indices = []
            # TODO: Materials

        def __str__(self):
            return f"{self.name}:\n\tvertexAttributes:{self.vertexAttribs}\n\tindices:{self.indices}\n"


def parse_model(file):
    objects = []

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

            if prefix == 'o':
                # TODO: handle origin
                vertexAttribList = []
                objects.append(mesh(values[0]))

            if prefix == 'v':
                vertices.append(values)
            if prefix == 'vn':
                normals.append(values)
            if prefix == 'vt':
                texCoords.append(values)

            if prefix == 'f':
                for point in values:
                    for i in range(len(vertexAttribList)):
                        if vertexAttribList[i] == point:
                            objects[-1].indices.append(i)
                            break;
                    else:
                        vertexAttribList.append(point)
                        vtn = [(int(c) - 1) for c in point.split('/')]
                        objects[-1].vertexAttribs.append(vertices[vtn[0]] + normals[vtn[2]] + texCoords[vtn[1]])
                        objects[-1].indices.append(len(objects[-1].vertexAttribs) - 1)

    return objects


def writeToFile(objects, outputFile):
    for o in objects:
        # nameLen > name
        # vertexAttributeLen > vertexAttributes (3 floats pos, 3 floats normals, 2 floats UV)
        # indicesLen > indices

        # name
        name_bytes = o.name.encode('utf-8')
        content = struct.pack('i', len(name_bytes)) + name_bytes
        print("nameLen: " + str(len(name_bytes)))
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
    objects = parse_model(inputFile)
    writeToFile(objects, outputFile)
