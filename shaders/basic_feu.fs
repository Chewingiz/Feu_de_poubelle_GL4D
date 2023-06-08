
/* Version GLSL 3.30 */
#version 330
/* texture 2 dimensions */
uniform sampler2D tex;
/* Le fragment shader est directement en relation avec les sorties du vertex shader */
in vec4 vsoColor;
in vec2 vsoTexCoord;
uniform int isTrans;
/* sortie du frament shader : une couleur */
out vec4 fragColor;

void main(void) {
  fragColor = texture(tex, vsoTexCoord) * vsoColor;
  if (isTrans==1){
    fragColor.a = 0.5;
  }
}
