#include <GeKo_Graphics\include.h>


int main()
{
	//*TEST AREA 2 TEST AREA 2 TEST AREA 2 TEST AREA 2 TEST AREA 2 TEST AREA 2*/

	/*Test: Fenster erstellen
	SUCCESS*/
	glfwInit();
	Window* window = new Window(100, 100, 800, 600, "Testarea");
	glewInit();

	/*Test: Shader binden und laden (Kevins Version)
	SUCCESS*/
	//Shader* redShader = new Shader("\\RedShader\\redShader.vert", ""/*geom*/, "" /*tessC*/, ""/*tessE*/, "\\RedShader\\redShader.frag", ""/*com*/);
	VertexShader vs(loadShaderSource(SHADERS_PATH + std::string("/ColorShader/colorShader.vert")));
	FragmentShader fs(loadShaderSource(SHADERS_PATH + std::string("/ColorShader/colorShader.frag")));
	ShaderProgram p(vs, fs);


	/*Test: Ein Szenegraph mit einem Rootnode und einem Node, der eine Geometrie hat
	Die Bufferdaten werden von der Geometrie gerendert
	Eine While-Schleife wird benutzt um die Geometrie zu rendern
	SUCCESS*/
	Rect* rectangle = new Rect();
	Scene* testScene = new Scene("Testscene");
	Node* testNode = new Node("testNode");
	testNode->addGeometry(rectangle);
	testNode->getGeometry();
	testScene->getScenegraph()->getRootNode()->addChildrenNode(testNode);
	testScene->getScenegraph()->getRootNode()->getChildrenNode("testNode");
	testScene->getScenegraph()->getRootNode()->getChildrenNode("testNode")->getGeometry()->loadBufferData();

	while (!glfwWindowShouldClose(window->getWindow()))
	{
		p.bind();
		p.sendVec3("color", glm::vec3(1.0, 0.0, 0.0));
		testScene->getScenegraph()->getRootNode()->getChildrenNode("testNode")->getGeometry()->renderGeometry();
		p.unbind();

		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();
	}



	return 0;
}