#include "Node.h"

#include "utils.h"

Node::Node() : rank(utils::getRank()), worldsize(utils::getWorldSize())
{
}