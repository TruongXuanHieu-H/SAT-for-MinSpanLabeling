#ifndef VERTICES_MODE_H
#define VERTICES_MODE_H

enum class VerticesMode
{
    no_hole,  // All the labels must be assigned. A label can be assigned to more than one vertex.
    has_hole, // A label must not be assigned to two or more vertices.
};

#endif