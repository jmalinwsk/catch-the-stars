void displayScene() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	for(Model m : models) {
		if(m.active)
			DrawModel(m);
	}

	glDisable(GL_DEPTH_TEST);
	for(Text t : texts)
		drawText(t);
	glEnable(GL_DEPTH_TEST);

	if(countdownTimerCounter == 0) {
		confettiModel->drawConfetti();
        keyboardActive = false;
	}

	glUseProgram( 0 );
	glBindVertexArray( 0 );

	glutSwapBuffers();
}

void initialize() {
	glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
	glEnable(GL_DEPTH_TEST);
	frameCounter = 0;

	Program* program = new Program("shaders/phongVertex.glsl", "shaders/phongFragment.glsl");
	Program* skyboxProgram = new Program("shaders/skyboxVertex.glsl", "shaders/skyboxFragment.glsl");
	Program* confettiProgram = new Program("shaders/confettiVertex.glsl", "shaders/confettiFragment.glsl");

	Texture* skyboxTexture = new Texture(skyboxFiles);
	Texture* yellowTexture = new Texture("textures/yellow.png");
	Texture* grassTexture = new Texture("textures/grass.png");
	Texture* confettiTexture = new Texture("textures/confetti.png");

	ground = new Ground("models/ground.obj");

	Model groundModel(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, "models/ground.obj", program, grassTexture, false, false);
	Model skyboxModel(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 50.0f, "models/cube.obj", skyboxProgram, skyboxTexture, true, false);
	Model* oneConfettiModel = new Model(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.05f, "models/plane.obj", confettiProgram, confettiTexture, false, false);

	models.push_back(groundModel);
	models.push_back(skyboxModel);

	confettiModel = new ConfettiModel(oneConfettiModel);

	for (int i=0; i<40; i++) {
		float min = -15.0f;
		float max = 15.0f;
		float x = min + rand()/(float)RAND_MAX*(max-min);
	    float z = min + rand()/(float)RAND_MAX*(max-min);
		Model starModel(x, ground->getAltitude(glm::vec3(x, 0.0f, z)), z, 0.0f, 0.0f, 0.0f, 0.5f, "models/star.obj", program, yellowTexture, false, true);
		models.push_back(starModel);
	}

	Font* pixeledFont = new Font("fonts/Pixeled.ttf");
	Font* digitalDarkSystemFont = new Font("fonts/digital dark system.ttf");

	Text fpsText(std::to_string(frameCounter), 1160, 680, 0.2f, glm::vec3(0.92f, 0.2f, 0.83f), pixeledFont);
	Text starCounterText(std::to_string(starCounter), 25, 40, 1.5f, glm::vec3(1.0f, 0.64f, 0.95f), digitalDarkSystemFont);
	Text countdownTimerText(std::to_string(countdownTimerCounter), 25, 640, 0.5f, glm::vec3(0.92f, 0.2f, 0.83f), pixeledFont);

	texts.push_back(fpsText);
	texts.push_back(starCounterText);
	texts.push_back(countdownTimerText);
}