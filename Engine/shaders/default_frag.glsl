#version 330 core
out vec4 FragColor;
in vec2 texCoord;

uniform vec4 color;
uniform sampler2D texture0;
uniform bool hasTexture;

void main()
{
    //vec2 flippedTexCoord = vec2(texCoord.x, 1.0 - texCoord)
    if (hasTexture && color != vec4(-1.0)) {
        FragColor = texture(texture0, texCoord) * color;
    }
    else if (hasTexture && color == vec4(-1.0)) {
        FragColor = texture(texture0, texCoord);
    }
    else
        FragColor = color;
}
