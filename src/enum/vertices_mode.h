#ifndef VERTICES_MODE_H
#define VERTICES_MODE_H

enum class VerticesMode
{
    no_hole,    // All the labels must be assigned. A label can be assigned to more than one vertex.
    has_hole,   // Some labels may not be assigned to any vertex. A label can be assigned to more than one vertex.
    amo_vertex, // Some labels may not be assigned to any vertex. A label can only be assigned to at most one vertex.
};

#endif