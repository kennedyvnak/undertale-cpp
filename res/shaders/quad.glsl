#shader vertex
#version 450 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexCoord;
layout (location = 3) in int a_TexIndex;
layout (location = 4) in float a_TimeOffset;
layout (location = 5) in float a_TimeSpeed;

layout (std140, binding = 0) uniform Camera {
   mat4 u_ViewProjection;
};

struct VertexOutput {
   vec4 Color;
   vec2 TexCoord;
};

layout (location = 0) out VertexOutput Output;
layout (location = 3) out flat int v_TexIndex;
layout (location = 4) out float v_TimeSeed;
layout (location = 5) out float v_TimeSpeed;

void main()
{
   Output.Color = a_Color;
   Output.TexCoord = a_TexCoord;
   v_TexIndex = a_TexIndex;
   v_TimeSeed = a_TimeOffset;
   v_TimeSpeed = a_TimeSpeed;

   gl_Position = u_ViewProjection * vec4(a_Position, 0.0, 1.0);
}

#shader fragment
#version 450 core

layout (location = 0) out vec4 o_Color;

layout (std140, binding = 1) uniform TimeBlock {
   float time;
   float delta_time;
} Time;

struct VertexOutput {
   vec4 Color;
   vec2 TexCoord;
};

layout (location = 0) in VertexOutput Input;
layout (location = 3) in flat int v_TexIndex;
layout (location = 4) in float v_TimeSpeed;
layout (location = 5) in float v_TimeOffset;

layout (binding = 0) uniform sampler2D u_Textures[32];

void main()
{
	vec4 texColor = vec4(Input.Color.rgb, Input.Color.a * (0.75 + sin(Time.time * v_TimeSpeed + v_TimeOffset) * 0.25));
	texColor *= texture(u_Textures[v_TexIndex], Input.TexCoord);

   if (texColor.a == 0.0)
      discard;

   o_Color = texColor;
}