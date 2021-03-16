#include "igl_component.h"
#include "malloc.h"
#include "strings.h"

igl_component_t *igl_component_new()
{
    igl_component_t *cmp = malloc(sizeof(igl_component_t));
    memset(cmp, 0, sizeof(igl_component_t));
    return cmp;
}
