/**
 * constant values used in ring_buffer class.
 */
#ifndef TOY_BOX_CLASSES_CONTAINER_RING_BUFFER_CONSTANTS_H
#define TOY_BOX_CLASSES_CONTAINER_RING_BUFFER_CONSTANTS_H

#include <cstdlib>

namespace toy_box {

namespace ring_buffer_bits {

static const size_t kDummyMemmorySize = 1;
static const size_t kCapacityBase = 2;

using index_t = size_t;
using capacity_t = size_t;

} /* ring_buffer_bits */

} /* toy_box */

#endif
