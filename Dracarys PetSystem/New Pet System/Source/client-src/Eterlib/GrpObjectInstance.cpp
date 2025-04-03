# Search 

	void CGraphicObjectInstance::SetScaleWorld(float x, float y, float z)

# If have don't add Eterlib



# Search x2

	D3DXMatrixIdentity(&m_matScale);

# Add after x2

	D3DXMatrixIdentity(&m_matScaleWorld);


# Search

void CGraphicObjectInstance::Transform()

# Change

void CGraphicObjectInstance::Transform()
{
	m_worldMatrix = m_matScaleWorld * m_mRotation;
	m_worldMatrix._41 += m_v3Position.x;
	m_worldMatrix._42 += m_v3Position.y;
	m_worldMatrix._43 += m_v3Position.z;
}


# Add 


void CGraphicObjectInstance::SetScaleWorld(float x, float y, float z)
{
	m_v3Scale.x = x;
	m_v3Scale.y = y;
	m_v3Scale.z = z;
	D3DXMatrixScaling(&m_matScaleWorld, x, y, z);
}