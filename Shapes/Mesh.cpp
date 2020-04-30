#include "Geometries.hpp"
#include "paths.hpp"

//Mesh member functions
Mesh::Mesh() : triangles{}, bbox{}
{
	std::string path{ ShaderPath };
	auto obj = atlas::utils::loadObjMesh(path + "teapot.obj", path + "default.mtl");
	std::vector<std::shared_ptr<Shape>> triangleset{};
	std::size_t index1, index2, index3;

	xmin = std::numeric_limits<float>::max();
	ymin = std::numeric_limits<float>::max();
	zmin = std::numeric_limits<float>::max();
	xmax = std::numeric_limits<float>::min();
	ymax = std::numeric_limits<float>::min();
	zmax = std::numeric_limits<float>::min();

	if (obj.has_value()) {
		auto teapot = obj.value();
		for (auto shape : teapot.shapes) {
			for (std::size_t i{ 0 }; i < shape.indices.size(); i += 3) {
				index1 = shape.indices[i];
				index2 = shape.indices[i + 1];
				index3 = shape.indices[i + 2];
				glm::vec4 pos1{ glm::vec4(shape.vertices[index1].position, 1.0f) };
				glm::vec4 pos2{ glm::vec4(shape.vertices[index2].position, 1.0f) };
				glm::vec4 pos3{ glm::vec4(shape.vertices[index3].position, 1.0f) };


				auto transform{ glm::rotate(math::Matrix4(1.0f), glm::radians(180.0f),  math::Vector{0.0f, 0.0f, 1.0f}) };
				transform = glm::rotate(transform, glm::radians(90.0f), math::Vector{ 0.0f, 1.0f, 0.0f });

				pos1 = transform * pos1;
				pos2 = transform * pos2;
				pos3 = transform * pos3;

				std::shared_ptr<Shape> temp{ std::make_shared<Triangle>(Triangle{ pos1, pos2, pos3 }) };
				temp->setColour({ 1.0f, 0.0f, 1.0f });
				temp->setMaterial(std::make_shared<Matte>(Matte{ 1.0f, Colour{1.0f, 0.0f, 1.0f} }));
				triangleset.push_back(temp);

				xmin = std::min(std::min(xmin, pos1.x), std::min(pos2.x, pos3.x));
				xmax = std::max(std::max(xmax, pos1.x), std::max(pos2.x, pos3.x));

				ymin = std::min(std::min(ymin, pos1.y), std::min(pos2.y, pos3.y));
				ymax = std::max(std::max(ymax, pos1.y), std::max(pos2.y, pos3.y));

				zmin = std::min(std::min(zmin, pos1.z), std::min(pos2.z, pos3.z));
				zmax = std::max(std::max(zmax, pos1.z), std::max(pos2.z, pos3.z));


			}
		}
	}
	//std::cout << ymin << " " << ymax;
	setBBox(std::make_shared<BoundingBox>(BoundingBox{ xmin, xmax, ymin, ymax, zmin, zmax }));
	setTriangles(triangleset);
}

std::shared_ptr<BoundingBox> Mesh::getBBox() {
	return bbox;
}

void Mesh::setBBox(std::shared_ptr<BoundingBox> const& box) {
	bbox = box;
}

void Mesh::setTriangles(std::vector<std::shared_ptr<Shape>> const& mesh) {
	triangles = mesh;
}

bool Mesh::hit(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr) {
	bool hit = false;
	if (bbox->hit(ray, sr)) {
		for (auto triangle : triangles) {
			if (triangle->hit(ray, sr)) {
				hit = true;
			}
		}
	}
	return hit;
}
