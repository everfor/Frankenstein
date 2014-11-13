#version 330

in vec2 tex0;
in vec3 normal0;
in vec3 worldPos0;

out vec4 gl_FragColor;

struct BaseLight
{
	vec3 color;
	float intensity;
};

struct Attenuation
{
	float constant;
	float linear;
	float exponent;
};

struct PointLight
{
	BaseLight base;
	Attenuation atten;
	vec3 position;
	float range;
};

uniform vec3 eyePos;
uniform sampler2D diffuse;

uniform float specularIntensity;
uniform float specularExponent;

uniform PointLight pointLight;

vec4 calculateLight(BaseLight base, vec3 direction, vec3 normal)
{
	float diffuseFactor = dot(normal, -direction);
	vec4 diffuseColor = vec4(0, 0, 0, 0);

	vec4 specularColor = vec4(0, 0, 0, 0);

	if (diffuseFactor > 0)
	{
		// Directional Lighting
		diffuseColor = vec4(base.color, 1.0) * base.intensity * diffuseFactor;

		// Specular Reflection
		vec3 directionToEye = normalize(eyePos - worldPos0);
		vec3 reflectDirection = normalize(reflect(direction, normal));

		float specularFactor = dot(directionToEye, reflectDirection);
		specularFactor = pow(specularFactor, specularExponent);

		if (specularFactor > 0)
		{
			specularColor = vec4(base.color, 1.0) * specularIntensity * specularFactor;
		}
	}

	return diffuseColor + specularColor;
}

vec4 calculatePointLight(PointLight pointLight, vec3 normal)
{
	vec3 lightDirecion = worldPos0 - pointLight.position;
	float distanceToPoint = length(lightDirecion);

	if (pointLight.range <= distanceToPoint)
	{
		return vec4(0, 0, 0, 0);
	}

	lightDirecion = normalize(lightDirecion);

	vec4 color = calculateLight(pointLight.base, lightDirecion, normal);

	// Attenuation
	float attenuation = pointLight.atten.constant 
						+ pointLight.atten.linear * distanceToPoint 
						+ pointLight.atten.exponent * distanceToPoint * distanceToPoint
						+ 0.0001;

	return color / attenuation;
}

void main()
{
	gl_FragColor = texture(diffuse, tex0.xy) * calculatePointLight(pointLight, normalize(normal0));
}