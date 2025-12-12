#ifndef GGLENGINE_GMDL_SERIALIZER_H
#define GGLENGINE_GMDL_SERIALIZER_H

#include <vector>
#include <bits/stdc++.h>
#include "Vertex.h"

struct GMDLSerializer {
    void _WriteGMDL(std::vector<Vertex>&, std::vector<uint16_t> indicies);
    void _LoadGMDL();
};

#endif