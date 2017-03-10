#version 410

in vec4 vPosition;
in vec2 vUV;
in vec3 vNormal;
in vec3 vTangent;
in vec3 vBiTangent;

// Material
uniform vec3 ambientMat = vec3(0,0,0); // ambient material color.
uniform sampler2D diffuseMap; // material diffuse map
uniform sampler2D specularMap; // material specular map
uniform sampler2D normalMap; // material normal map

// Lighting
uniform vec3 ambientLight = vec3(0.25f, 0.25f, 0.25f); // environment ambient light
uniform vec3 diffuseLight = vec3(1,1,1);	 // environment diffuse light
uniform vec3 specularLight = vec3(1,1,1);	 // environment specular light
uniform float specularLightPower = 32.0f; // specular power

uniform vec3 cameraPos; // world-space camera position
uniform vec3 lightDir; // normalised light direction from light
uniform float roughness; // surface roughness

out vec4 fragColour;

void main()
{
	// LAMBERT ---> NOT WORKING ------------------
	// Calculate Normal
	vec3 uvNormal = texture( normalMap, vUV ).xyz * 2 - 1; // Normal from Map
	mat3 TBN = mat3( 	normalize( vTangent ),		// UV to Object-space matrix
			 			normalize( vBiTangent ),
						normalize( vNormal ) );
	vec3 fNormal = uvNormal * TBN;
	// ----------------

	vec3 Ambient = ambientMat * ambientLight; // ambient light
	
	float NdL = max( 0.0f, dot( vNormal, -lightDir ) ); // Lambert Term
	vec3 Diffuse = texture( diffuseMap, vUV ).xyz * diffuseLight; // diffuse light for 1 light

	vec3 R = reflect( lightDir, vNormal );	//reflected light vector
	vec3 E = normalize( cameraPos - vPosition.xyz );	// surface-to-eye vector

	float specTerm = pow( min( 0.0f, dot( R, E ) ), specularLightPower ); // Specular Term
	vec3 Specular = texture( specularMap, vUV ).xyz * specularLight * specTerm; // specular light for 1 light

	fragColour = vec4(Ambient + Diffuse + Specular, 1.0f);
	// -------------------------------------------



	//float d = max( 0, dot(normalize( TBN * uvNormal ), normalize(lightDir)));


	// vec3 AmbientL = kA * iA;	// ambient light
	
	// float Ndl = max( 0.0f, dot( N, -L ) );	// Lambert term
	// vec3 DiffuseL = vec3( texture( kD, vUV ) ) * iD * Ndl;	// diffuse ligt for one light
	
	//vec3 R = reflect( -lightDir, uvNormal );	//reflected light vector
	//vec3 E = normalize( cameraPos - vPosition.xyz );	// surface-to-eye vector
	//float s = max( 0, dot( E, R ) );
	//s = pow( s, specularLightPower );
	// float specTerm = pow( min ( 0.0f, dot( R, E ) ), specularLightPower );	// Specular term
	// vec3 SpecularL = vec3( texture( kS, vUV ) ) * iS * specTerm;	// specular light for one light

	// fragColour = vec4(AmbientL + DiffuseL + SpecularL, 1);
	//fragColour = vec4(ambientLight * d + ambientLight * s * fragColour.rgb, 1);

	//fragColour = texture(kD, vUV);
	//fragColour.rgb = fragColour.rgb * d;
}