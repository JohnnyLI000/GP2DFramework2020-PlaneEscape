// COMP710 GP 2D Framework 2020
#ifndef __SPRITE_H__
#define __SPRITE_H__

// Forward Declarations:
class BackBuffer;
class Texture;

class Sprite
{
	//Member Methods:
public:
	Sprite();
	~Sprite();

	bool Initialise(Texture& texture);

	void Process(float deltaTime);
	void Draw(BackBuffer& backbuffer);

	void DrawScale(BackBuffer& backbuffer, float scale);

	void SetX(float x);
	void SetY(float y);

	float GetX() const;
	float GetY() const;

	void SetAngle(float angle);
	float GetAngle() const;

	void SetCenter(float x, float y);
	void SetHandleCenter();

	int GetWidth() const;
	int GetHeight() const;

	Texture* GetTexture();

protected:

private:
	Sprite(const Sprite& sprite);
	Sprite& operator=(const Sprite& sprite);

	//Member Data:
public:

protected:
	Texture* m_pTexture;
	float m_x;
	float m_y;

	float m_angle;
	float m_centerX;
	float m_centerY;

	int m_width;
	int m_height;

private:

};

#endif // __SPRITE_H__
