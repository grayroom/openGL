#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D textureBack;
uniform sampler2D textureFront;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = mix(texture(textureFront, TexCoord), texture(textureBack, TexCoord), 0.2);
}