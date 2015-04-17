#include "Effect.h"

using namespace tinyxml2;

Effect::Effect()
{
	emitterVec.clear();
	setName("unnamedEffect");
}

Effect::Effect(std::string name)
{
	emitterVec.clear();
	setName(name);
}

Effect::Effect(const char*filepath)
{
	//TODO
	emitterVec.clear();
	loadEffect(filepath);
}

Effect::~Effect()
{
	//TODO
	emitterVec.~vector();
}


//void Effect::active()
//{
//	for (auto emitter : emitterVec){
//		emitter->active();
//	}
//}

void Effect::addEmitter(Emitter* emitter)
{
	emitterVec.push_back(emitter);
}

void Effect::removeEmitter(int arrayPosition)
{
	emitterVec.erase(emitterVec.begin() + arrayPosition);
}

void Effect::changePosition(glm::vec3 newPosition)
{
	for (auto emitter : emitterVec){
		emitter->setPosition(newPosition);
	}
}

void Effect::updateEmitters()
{
	for (auto emitter : emitterVec){
		emitter->generateParticle();
		emitter->update();
	}
}

void Effect::renderEmitters(Camera &cam)
{
	for (auto emitter : emitterVec){
		emitter->render(cam);
	}
}


int Effect::loadEffect(const char* filepath)
{
	//load file
	XMLDocument doc;
	XMLError error = doc.LoadFile(filepath);
	XMLCheckResult(error);

	XMLNode* effectNode = doc.FirstChild();
	if (effectNode == nullptr) return XML_ERROR_FILE_READ_ERROR;

	XMLElement* emitterNode = effectNode->FirstChildElement("Emitter");

	while (emitterNode != nullptr)
	{
	/****Constructor stuff****/
		int outputType;
		XMLElement* item = emitterNode->FirstChildElement("OutputType");
		if (item == nullptr) return XML_ERROR_PARSING_ELEMENT;
		error = item->QueryIntText(&outputType);
		XMLCheckResult(error);

		glm::vec3 position;
		item = emitterNode->FirstChildElement("Position");
		if (item == nullptr) return XML_ERROR_PARSING_ELEMENT;
		error = item->QueryFloatAttribute("x", &position.x);
		XMLCheckResult(error);
		error = item->QueryFloatAttribute("y", &position.y);
		XMLCheckResult(error);
		error = item->QueryFloatAttribute("z", &position.z);
		XMLCheckResult(error);

		double emitterLifetime;
		item = emitterNode->FirstChildElement("EmitterLifetime");
		if (item == nullptr) return XML_ERROR_PARSING_ELEMENT;
		error = item->QueryDoubleText(&emitterLifetime);
		XMLCheckResult(error);

		double emitFrequency;
		item = emitterNode->FirstChildElement("EmitFrequency");
		if (item == nullptr) return XML_ERROR_PARSING_ELEMENT;
		error = item->QueryDoubleText(&emitFrequency);
		XMLCheckResult(error);

		int particlesPerEmit;
		item = emitterNode->FirstChildElement("ParticlesPerEmit");
		if (item == nullptr) return XML_ERROR_PARSING_ELEMENT;
		error = item->QueryIntText(&particlesPerEmit);
		XMLCheckResult(error);

		double particleLifetime;
		item = emitterNode->FirstChildElement("ParticleLiftime");
		if (item == nullptr) return XML_ERROR_PARSING_ELEMENT;
		error = item->QueryDoubleText(&particleLifetime);
		XMLCheckResult(error);

		bool particleMortal;
		item = emitterNode->FirstChildElement("ParticleMortal");
		if (item == nullptr) return XML_ERROR_PARSING_ELEMENT;
		error = item->QueryBoolText(&particleMortal);
		XMLCheckResult(error);

		//create an Emitter
		Emitter* emitter = new Emitter(outputType, position, emitterLifetime, 
			emitFrequency, particlesPerEmit, particleLifetime, particleMortal);

	/****other necessary stuff****/
		//Geometry Shader
		item = emitterNode->FirstChildElement("UseGeometryShader");
		if (item == nullptr) return XML_ERROR_PARSING_ELEMENT;
		bool geom;
		error = item->QueryBoolText(&geom);
		XMLCheckResult(error);
		if (geom) emitter->switchToGeometryShader();

		//Velocity
		item = emitterNode->FirstChildElement("Velocity");
		if (item != nullptr){
			int velocity;
			error = item->QueryIntText(&velocity);
			XMLCheckResult(error);
			emitter->setVelocity(velocity);
		}

		//Physic
		item = emitterNode->FirstChildElement("Physic");
		if (item != nullptr) 
		{
			XMLElement* physicType = item->FirstChildElement("Trajectory");
			if (physicType != nullptr){
				XMLElement* physicElement = physicType->FirstChildElement("Gravity");
				if (physicElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
				glm::vec4 gravity;
				error = physicElement->QueryFloatAttribute("x", &gravity.x);
				XMLCheckResult(error);
				error = physicElement->QueryFloatAttribute("y", &gravity.y);
				XMLCheckResult(error);
				error = physicElement->QueryFloatAttribute("z", &gravity.z);
				XMLCheckResult(error);
				error = physicElement->QueryFloatAttribute("w", &gravity.w);
				XMLCheckResult(error);

				physicElement = physicType->FirstChildElement("Speed");
				if (physicElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
				float speed;
				error = physicElement->QueryFloatText(&speed);
				XMLCheckResult(error);

				emitter->usePhysicTrajectory(gravity, speed);
			} 
			physicType = item->FirstChildElement("DirectionGravity");
			if (physicType != nullptr){
				XMLElement* physicElement = physicType->FirstChildElement("Gravity");
				if (physicElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
				glm::vec4 gravity;
				error = physicElement->QueryFloatAttribute("x", &gravity.x);
				XMLCheckResult(error);
				error = physicElement->QueryFloatAttribute("y", &gravity.y);
				XMLCheckResult(error);
				error = physicElement->QueryFloatAttribute("z", &gravity.z);
				XMLCheckResult(error);
				error = physicElement->QueryFloatAttribute("w", &gravity.w);
				XMLCheckResult(error);

				physicElement = physicType->FirstChildElement("Speed");
				if (physicElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
				float speed;
				error = physicElement->QueryFloatText(&speed);
				XMLCheckResult(error);

				emitter->usePhysicDirectionGravity(gravity, speed);
			}
			physicType = item->FirstChildElement("PointGravity");
			if (physicType != nullptr){
				XMLElement* physicElement = physicType->FirstChildElement("Gravity");
				if (physicElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
				glm::vec4 gravity;
				error = physicElement->QueryFloatAttribute("x", &gravity.x);
				XMLCheckResult(error);
				error = physicElement->QueryFloatAttribute("y", &gravity.y);
				XMLCheckResult(error);
				error = physicElement->QueryFloatAttribute("z", &gravity.z);
				XMLCheckResult(error);
				error = physicElement->QueryFloatAttribute("w", &gravity.w);
				XMLCheckResult(error);

				physicElement = physicType->FirstChildElement("Speed");
				if (physicElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
				float speed;
				error = physicElement->QueryFloatText(&speed);
				XMLCheckResult(error);
			
				physicElement = physicType->FirstChildElement("GravityRange");
				if (physicElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
				float gravityRange;
				error = physicElement->QueryFloatText(&gravityRange);
				XMLCheckResult(error);

				physicElement = physicType->FirstChildElement("GravityFunction");
				if (physicElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
				int gravityFunction;
				error = physicElement->QueryIntText(&gravityFunction);
				XMLCheckResult(error);

				emitter->usePhysicPointGravity(gravity, gravityRange, gravityFunction,speed);
			}
			physicType = item->FirstChildElement("SwarmCircleMotion");
			if (physicType != nullptr){
				XMLElement* physicElement = physicType->FirstChildElement("MovementVertical");
				if (physicElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
				bool movementVertical;
				error = physicElement->QueryBoolText(&movementVertical);
				XMLCheckResult(error);
			
				physicElement = physicType->FirstChildElement("MovementHorizontalX");
				if (physicElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
				bool movementHorizontalX;
				error = physicElement->QueryBoolText(&movementHorizontalX);
				XMLCheckResult(error);

				physicElement = physicType->FirstChildElement("MovementHorizontalZ");
				if (physicElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
				bool movementHorizontalZ;
				error = physicElement->QueryBoolText(&movementHorizontalZ);
				XMLCheckResult(error);

				//physicElement = physicType->FirstChildElement("MovementLength");
				//if (physicElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
				//float movementLength;
				//error = physicElement->QueryFloatText(&movementLength);
				//XMLCheckResult(error);

				emitter->usePhysicSwarmCircleMotion(movementVertical, movementHorizontalX, movementHorizontalZ);
			}
		}

		//Area Emitter
		item = emitterNode->FirstChildElement("AreaEmitter");
		if (item != nullptr){
			bool on;
			error = item->QueryBoolAttribute("on", &on);
			XMLCheckResult(error);
			if (on) {
				XMLElement* area = item->FirstChildElement("AreaXY");
				if (area == nullptr) return XML_ERROR_PARSING_ELEMENT;
				bool areaXY;
				error = area->QueryBoolText(&areaXY);
				XMLCheckResult(error);
				
				area = item->FirstChildElement("AreaXZ");
				bool areaXZ;
				error = area->QueryBoolText(&areaXZ);
				XMLCheckResult(error);

				area = item->FirstChildElement("Size");
				float size;
				error = area->QueryFloatText(&size);
				XMLCheckResult(error);

				area = item->FirstChildElement("Accuracy");
				int accuracy;
				error = area->QueryIntText(&accuracy);
				XMLCheckResult(error);

				emitter->setAreaEmitting(areaXY, areaXZ, size, accuracy);
			}
		}
		//Texures
		item = emitterNode->FirstChildElement("Texture");
		if (item != nullptr){
			//addTexture
			XMLElement* tex = item->FirstChildElement("Tex");
			while (tex != nullptr){
				std::string filepath = tex->GetText();
				std::string spath = RESOURCES_PATH + filepath;
				char* cpath = new char[spath.length() + 1];
				strcpy(cpath, spath.c_str());

				Texture* texture = new Texture(cpath);
				emitter->addTexture(texture, 0.0);

				tex = tex->NextSiblingElement("Tex");
			}

			//useTexture
			XMLElement* scaling = item->FirstChildElement("Scaling");
			if (scaling != nullptr) {
				bool useTexture;
				XMLElement* tex = scaling->FirstChildElement("UseTexture");
				error = tex->QueryBoolText(&useTexture);
				XMLCheckResult(error);

				std::vector<float> scalingSize;
				tex = scaling->FirstChildElement("ScalingSize");
				if (tex == nullptr) return XML_ERROR_PARSING_ELEMENT;
				XMLElement* temp = tex->FirstChildElement("Item");
				while (temp != nullptr){
					float value;
					error = temp->QueryFloatText(&value);
					XMLCheckResult(error);
					scalingSize.push_back(value);

					temp = temp->NextSiblingElement("Item");
				}
				
				std::vector<float> scalingMoment;
				tex = scaling->FirstChildElement("ScalingMoment");
				if (tex == nullptr) return XML_ERROR_PARSING_ELEMENT;
				temp = tex->FirstChildElement("Item");
				while (temp != nullptr){
					float value;
					error = temp->QueryFloatText(&value);
					XMLCheckResult(error);
					scalingMoment.push_back(value);

					temp = temp->NextSiblingElement("Item");
				}

				float birthTime;
				tex = scaling->FirstChildElement("BirthTime");
				error = tex->QueryFloatText(&birthTime);
				XMLCheckResult(error);
				
				float deathTime;
				tex = scaling->FirstChildElement("DeathTime");
				error = tex->QueryFloatText(&deathTime);
				XMLCheckResult(error);

				bool rotateLeft;
				tex = scaling->FirstChildElement("RotateLeft");
				error = tex->QueryBoolText(&rotateLeft);
				XMLCheckResult(error);

				float rotationSpeed;
				tex = scaling->FirstChildElement("RotationSpeed");
				error = tex->QueryFloatText(&rotationSpeed);
				XMLCheckResult(error);

				emitter->useTexture(useTexture, scalingSize, scalingMoment, 
					birthTime, deathTime, rotateLeft, rotationSpeed);
			}
			else {
				scaling = item->FirstChildElement("Size");
				if (scaling == nullptr) return XML_ERROR_PARSING_ELEMENT;
				
				bool useTexture;
				XMLElement* tex = scaling->FirstChildElement("UseTexture");
				error = tex->QueryBoolText(&useTexture);
				XMLCheckResult(error);

				float particleSize;
				tex = scaling->FirstChildElement("ParticleSize");
				error = tex->QueryFloatText(&particleSize);
				XMLCheckResult(error);

				float birthTime;
				tex = scaling->FirstChildElement("BirthTime");
				error = tex->QueryFloatText(&birthTime);
				XMLCheckResult(error);

				float deathTime;
				tex = scaling->FirstChildElement("DeathTime");
				error = tex->QueryFloatText(&deathTime);
				XMLCheckResult(error);

				bool rotateLeft;
				tex = scaling->FirstChildElement("RotateLeft");
				error = tex->QueryBoolText(&rotateLeft);
				XMLCheckResult(error);

				float rotationSpeed;
				tex = scaling->FirstChildElement("RotationSpeed");
				error = tex->QueryFloatText(&rotationSpeed);
				XMLCheckResult(error);

				emitter->useTexture(useTexture, particleSize, 
					birthTime, deathTime, rotateLeft, rotationSpeed);
			}
			
		}

		//next Emitter
		emitterVec.push_back(emitter);
		emitterNode = emitterNode->NextSiblingElement("Emitter");
	}

	printf("EFFECT: loading Effect successfully\n");
	return XML_SUCCESS;
}

int Effect::saveEffect(char* filepath)
{
	XMLDocument doc;
	XMLNode* effect = doc.NewElement("Effect");
	doc.InsertFirstChild(effect);
	for (auto emitter : emitterVec)
	{
	/****Constructor stuff****/
		XMLNode* emitterNode = doc.NewElement("Emitter");
		effect->InsertEndChild(emitterNode);

		XMLElement* element = doc.NewElement("OutputType");
		element->SetText(emitter->getOutputMode());
		emitterNode->InsertEndChild(element);

		element = doc.NewElement("Position");
		glm::vec3 position = emitter->getPosition();
		element->SetAttribute("x", position.x);
		element->SetAttribute("y", position.y);
		element->SetAttribute("z", position.z);
		emitterNode->InsertEndChild(element);

		element = doc.NewElement("EmitterLifetime");
		element->SetText(emitter->getEmitterLifetime());
		emitterNode->InsertEndChild(element);

		element = doc.NewElement("EmitFrequency");
		element->SetText(emitter->getEmitFrequency());
		emitterNode->InsertEndChild(element);

		element = doc.NewElement("ParticlesPerEmit");
		element->SetText(emitter->getParticlesPerEmit());
		emitterNode->InsertEndChild(element);

		element = doc.NewElement("ParticleLiftime");
		element->SetText(emitter->getParticleLifetime());
		emitterNode->InsertEndChild(element);

		element = doc.NewElement("ParticleMortal");
		element->SetText(emitter->getParticleMortality());
		emitterNode->InsertEndChild(element);

	/****other necessary stuff****/
		//Geometry Shader
		element = doc.NewElement("UseGeometryShader");
		element->SetText(emitter->getUseGeometryShader());
		emitterNode->InsertEndChild(element);
		
		//Velocity
		element = doc.NewElement("Velocity");
		element->SetText(emitter->getVelocityType());
		emitterNode->InsertEndChild(element);

		//Physic
		element = doc.NewElement("Physic");
		if (emitter->m_useTrajectory){
			XMLElement* physic = doc.NewElement("Trajectory");
			XMLElement* gravity = doc.NewElement("Gravity");
			glm::vec4 gravityVec = emitter->getGravity();
			gravity->SetAttribute("x", gravityVec.x);
			gravity->SetAttribute("y", gravityVec.y);
			gravity->SetAttribute("z", gravityVec.z);
			gravity->SetAttribute("w", gravityVec.w);
			physic->InsertEndChild(gravity);

			XMLElement* speed = doc.NewElement("Speed");
			speed->SetText(emitter->getSpeed());
			physic->InsertEndChild(speed);
			element->InsertEndChild(physic);
		}
		else if (emitter->m_useDirectionGravity){
			XMLElement* physic = doc.NewElement("DirectionGravity");
			XMLElement* temp = doc.NewElement("Gravity");
			glm::vec4 gravityVec = emitter->getGravity();
			temp->SetAttribute("x", gravityVec.x);
			temp->SetAttribute("y", gravityVec.y);
			temp->SetAttribute("z", gravityVec.z);
			temp->SetAttribute("w", gravityVec.w);
			physic->InsertEndChild(temp);

			temp = doc.NewElement("Speed");
			temp->SetText(emitter->getSpeed());
			physic->InsertEndChild(temp);
			element->InsertEndChild(physic);
		}
		else if (emitter->m_usePointGravity){
			XMLElement* physic = doc.NewElement("PointGravity");
			XMLElement* temp = doc.NewElement("Gravity");
			glm::vec4 gravityVec = emitter->getGravity();
			temp->SetAttribute("x", gravityVec.x);
			temp->SetAttribute("y", gravityVec.y);
			temp->SetAttribute("z", gravityVec.z);
			temp->SetAttribute("w", gravityVec.w);
			physic->InsertEndChild(temp);

			temp = doc.NewElement("Speed");
			temp->SetText(emitter->getSpeed());
			physic->InsertEndChild(temp);

			temp = doc.NewElement("GravityRange");
			temp->SetText(emitter->m_gravityRange);
			physic->InsertEndChild(temp);

			temp = doc.NewElement("GravityFunction");
			temp->SetText(emitter->m_gravityFunction);
			physic->InsertEndChild(temp);
			element->InsertEndChild(physic);
		}
		else if (emitter->m_useChaoticSwarmMotion){
			XMLElement* physic = doc.NewElement("SwarmCircleMotion");
			XMLElement* temp = doc.NewElement("MovementVertical");
			temp->SetText(emitter->m_movementVertical);
			physic->InsertEndChild(temp);

			temp = doc.NewElement("MovementHorizontalX");
			temp->SetText(emitter->m_movementHorizontalX);
			physic->InsertEndChild(temp);

			temp = doc.NewElement("MovementHorizontalZ");
			temp->SetText(emitter->m_movementHorizontalZ);
			physic->InsertEndChild(temp);

			//temp = doc.NewElement("MovementLength");
			//temp->SetText(emitter->m_movementLength);
			//physic->InsertEndChild(temp);
			element->InsertEndChild(physic);
		}
		emitterNode->InsertEndChild(element);

		//Area emitting
		element = doc.NewElement("AreaEmitter");
		bool on = emitter->getAreaEmittingXY() | emitter->getAreaEmittingXZ();
		element->SetAttribute("on", on);
		if (on){
			XMLElement* temp = doc.NewElement("AreaXY");
			temp->SetText(emitter->getAreaEmittingXY());
			element->InsertEndChild(temp);

			temp = doc.NewElement("AreaXZ");
			temp->SetText(emitter->getAreaEmittingXZ());
			element->InsertEndChild(temp);

			temp = doc.NewElement("Size");
			temp->SetText(emitter->getAreaSize());
			element->InsertEndChild(temp);

			temp = doc.NewElement("Accuracy");
			temp->SetText(emitter->getAreaAccuracy());
			element->InsertEndChild(temp);
		}
		emitterNode->InsertEndChild(element);

		//Textures
		element = doc.NewElement("Texture");
		for (auto texture : emitter->m_textureList)
		{
			XMLElement* tex = doc.NewElement("Tex");
			tex->SetText(texture->getFilepath());
			element->InsertEndChild(tex);
		}

		if (emitter->m_useScaling) {
			XMLElement* scaling = doc.NewElement("Scaling");
			
			XMLElement* tex = doc.NewElement("UseTexture");
			tex->SetText(emitter->getUseTexture());
			scaling->InsertEndChild(tex);

			tex = doc.NewElement("ScalingSize");
			for (int i = 1; i < emitter->m_scalingCount; i = i + 2){
				XMLElement* item = doc.NewElement("Item");
				item->SetText(emitter->m_scalingData[i]);
				tex->InsertEndChild(item);
			}
			scaling->InsertEndChild(tex);
			
			tex = doc.NewElement("ScalingMoment");
			for (int i = 0; i < emitter->m_scalingCount; i = i + 2){
				XMLElement* item = doc.NewElement("Item");
				item->SetText(emitter->m_scalingData[i]);
				tex->InsertEndChild(item);
			}
			scaling->InsertEndChild(tex);			

			tex = doc.NewElement("BirthTime");
			tex->SetText(emitter->m_birthTime);
			scaling->InsertEndChild(tex);

			tex = doc.NewElement("DeathTime");
			tex->SetText(emitter->m_deathTime);
			scaling->InsertEndChild(tex);

			tex = doc.NewElement("RotateLeft");
			tex->SetText(emitter->m_rotateLeft);
			scaling->InsertEndChild(tex);

			tex = doc.NewElement("RotationSpeed");
			tex->SetText(emitter->getRotationSpeed());
			scaling->InsertEndChild(tex);

			element->InsertEndChild(scaling);
		}
		else {
			XMLElement* scaling = doc.NewElement("Size");

			XMLElement* tex = doc.NewElement("UseTexture");
			tex->SetText(emitter->getUseTexture());
			scaling->InsertEndChild(tex);

			tex = doc.NewElement("ParticleSize");
			tex->SetText(emitter->particleDefaultSize);
			scaling->InsertEndChild(tex);

			tex = doc.NewElement("BirthTime");
			tex->SetText(emitter->m_birthTime);
			scaling->InsertEndChild(tex);

			tex = doc.NewElement("DeathTime");
			tex->SetText(emitter->m_deathTime);
			scaling->InsertEndChild(tex);

			tex = doc.NewElement("RotateLeft");
			tex->SetText(emitter->m_rotateLeft);
			scaling->InsertEndChild(tex);

			tex = doc.NewElement("RotationSpeed");
			tex->SetText(emitter->getRotationSpeed());
			scaling->InsertEndChild(tex);

			element->InsertEndChild(scaling);
		}
		emitterNode->InsertEndChild(element);
	}

	//save the file
	XMLError error = doc.SaveFile(filepath);
	XMLCheckResult(error);
	printf("EFFECT: saving Effect successfully\n");
	return XML_SUCCESS;
}


void Effect::setName(std::string name)
{
	effectName = name;
}

std::string Effect::getName()
{
	return effectName;
}