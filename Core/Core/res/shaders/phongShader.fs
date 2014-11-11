#version 330

const int MAX_POINT_LIGHTS  = 4;
const int MAX_SPOT_LIGHTS  = 4;

in vec2 tex0;
in vec3 normal0;
in vec3 worldPos0;

out vec4 gl_FragColor;

struct BaseLight
{
	vec3 color;
	float intensity;
};

struct DirectionalLight
{
	BaseLight base;
	vec3 direction;
};

// For point light
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

struct SpotLight
{
	PointLight pointLight;
	vec3 direction;
	float cutoff;
};

uniform vec3 baseColor;
uniform vec3 ambientLight;
uniform vec3 eyePos;
uniform sampler2D sampler;

uniform float specularIntensity;
uniform float specularExponent;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

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

vec4 calculateDirectionalLight(DirectionalLight directionalLight, vec3 normal)
{
	return calculateLight(directionalLight.base, directionalLight.direction, normal);
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

vec4 calcualteSpotLight(SpotLight spotLight, vec3 normal)
{
	vec3 lightDirection = normalize(worldPos0 - spotLight.pointLight.position);
	float spotFactor = dot(lightDirection, spotLight.direction);

	vec4 color = vec4(0, 0, 0, 0);

	if (spotFactor > spotLight.cutoff)
	{
		color = calculatePointLight(spotLight.pointLight, normal)
				* (1.0 - (1.0 - spotFactor) / (1.0 - spotLight.cutoff));
	}

	return color;
}

void main()
{
	vec4 textureColor = texture(sampler, tex0.xy);
	vec4 color = vec4(baseColor, 1.0);

	// Lighting
	vec4 totalLight = vec4(ambientLight, 1.0);

	if (textureColor != vec4(0, 0, 0, 0))
	{
		color *= textureColor;
	}

	// Directional Light
	vec3 normal = normalize(normal0);
	totalLight += calculateDirectionalLight(directionalLight, normal);

	// Point Light
	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		if (pointLights[i].base.intensity > 0)
		{
			totalLight += calculatePointLight(pointLights[i], normal);
		}
	}

	// Spot Light
	for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
		if (spotLights[i].pointLight.base.intensity > 0)
		{
			totalLight += calcualteSpotLight(spotLights[i], normal);
		}
	}

	gl_FragColor = color * totalLight;
}
