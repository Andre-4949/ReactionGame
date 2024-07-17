#include <utility>
#include "../../include/Scene/KittiObject.h"
#include "../../include/PreGameControlling/Game.h"

void KittiObject::render()
{
	this->label.getBoundingBox().render();
}

void KittiObject::setColor(const cv::Scalar & color)
{
	this->label.getBoundingBox().setColor(color);
}

const bool KittiObject::processClicks(const int x, const int y)
{
	return this->label.getBoundingBox().getClicked(x, y);
}

Label & KittiObject::getLabel()
{
	return this->label;
}

KittiObject::KittiObject(const Label label): label(std::move(label))
{}

KittiObject::KittiObject() = default;

bool KittiObject::operator==(KittiObject & other)
{
	return label.getBoundingBox() == other.getLabel().getBoundingBox();
}

bool KittiObject::operator!=(KittiObject & other)
{
	return !(*this == other);
}
