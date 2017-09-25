#ifndef MENU_H
#define MENU_H
#include"Includes.h"
class Menu : public sf::Drawable
{
private:
	//TODO: Button frame/clickboxes.
	sf::Texture menuTex;	
	sf::Sprite menuSprite;

	sf::Text carMenu	[5];
	sf::Text engineMenu	[5];
	sf::Text wheelMenu	[5];
	sf::Text courseMenu	[5];

	sf::Font menuFont;
	sf::FloatRect clickBoxes[5];

	enum Current_Menu currMenu;

	int carSelect;
	int engineSelect;
	int courseSelect;
	int wheelSelect;
	
	float cooldown;
	bool onCooldown;
public:
	Menu();
	~Menu();

	void draw(sf::RenderTarget &target, sf::RenderStates states)const;
	void update(sf::Window &window, float gameTime);

};
#endif