#include "Material.h""

Material::Material(const Material& mtl) {
	setEmission(mtl.getEmission()[0], mtl.getEmission()[1], mtl.getEmission()[2], mtl.getEmission()[3]);
	setAmbient(mtl.getAmbient()[0], mtl.getAmbient()[1], mtl.getAmbient()[2], mtl.getAmbient()[3]);
	setDiffuse(mtl.getDiffuse()[0], mtl.getDiffuse()[1], mtl.getDiffuse()[2], mtl.getDiffuse()[3]);
	setSpecular(mtl.getSpecular()[0], mtl.getSpecular()[1], mtl.getSpecular()[2], mtl.getSpecular()[3]);
	setShininess(mtl.getShininess()[0]);
};

void Material::setEmission(float r, float g, float b, float a) {
	emission[0] = r;
	emission[1] = g;
	emission[2] = b;
	emission[3] = a;

}
void Material::setAmbient(float r, float g, float b, float a) {
	ambient[0] = r;
	ambient[1] = g;
	ambient[2] = b;
	ambient[3] = a;


}
void Material::setDiffuse(float r, float g, float b, float a) {
	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	diffuse[3] = a;



}
void Material::setSpecular(float r, float g, float b, float a) {
	specular[0] = r;
	specular[1] = g;
	specular[2] = b;
	specular[3] = a;



}
void Material::setShininess(float sh) {
	shininess[0] = sh;




}




const float* Material::getEmission() const {

	return emission;


};
const float* Material::getAmbient() const {
	return ambient;

};
const float* Material::getDiffuse() const {
	return diffuse;

};
const float* Material::getSpecular() const {
	return specular;


};
const float* Material::getShininess() const {

	return shininess;

};