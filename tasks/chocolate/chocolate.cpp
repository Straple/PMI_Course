#include "chocolate.h"

bool CanBreakSlices(int height, int width, int slices_amount) {
    return height > 0 && width > 0 && slices_amount > 0 && slices_amount < height * width &&
           (slices_amount % width == 0 || slices_amount % height == 0);
}