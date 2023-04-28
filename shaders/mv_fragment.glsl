#version 410 core
in vec4 gl_FragCoord;
 
out vec4 FragColor;
 
#define MAX_ITERATIONS 1200

uniform int screen_w;
uniform int screen_h;
uniform float mouse_x;
uniform float mouse_y;
uniform float zoom;

float n = 0.0f;
float threshold = 100.0;

float mandelbrot(vec2 c) {
    vec2 z = vec2(0.0,0.0);
    for(int i = 0; i < MAX_ITERATIONS; i++ ) {
        vec2 znew;
        znew.x = (z.x * z.x ) - (z.y * z.y ) + c.x;
        znew.y = ( 2.0 * z.x * z.y) + c.y;
        z = znew;
        if((z.x * z.y) + (z.y * z.y) > threshold) {
            break;
        }
        n++;
    }
    return n/float(MAX_ITERATIONS);
}

vec4 farby(float t) {											
		float r = 9.0 * (1.0 - t) * t * t * t;								
		float g = 15.0 * (1.0 - t) * (1.0 - t) * t * t;						
		float b = 8.5 * (1.0 - t) * (1.0 - t) * (1.0 - t) * t;				
																			
		return vec4(r, g, b, 1.0);											
}
 
void main()
{
    vec2 coord = vec2(gl_FragCoord.xy);				
    coord = vec2(coord.x - screen_w/2, coord.y - screen_h/2);
    coord = coord/zoom;
    coord = vec2(coord.x - mouse_x, coord.y-mouse_y);

		float mb = mandelbrot(coord);	    
    FragColor = farby(mb);	
}
