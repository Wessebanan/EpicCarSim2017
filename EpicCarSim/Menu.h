#ifndef MENU_H
#define MENU_H
#include "Includes.h"
#include "GlobalDefs.h"
class Menu : public sf::Drawable
{
private:
	//TODO: Button frame/clickboxes or not.
	sf::Texture menuTex;	
	sf::Sprite menuSprite;

	sf::Text carMenu	[nCars];
	sf::Text engineMenu	[nEngines];
	sf::Text wheelMenu	[nWheels];
	sf::Text courseMenu	[nCourses];

	sf::Font menuFont;
	sf::FloatRect clickBoxes[5];

	enum CurrentMenu currMenu;

	struct Selects selects;
	
	float cooldown;
	bool onCooldown;
public:
	Menu(std::string cars[], std::string engines[], std::string wheels[], std::string courses[]);
	~Menu();

	struct Selects getSelects();
	enum CurrentMenu getMenuState();

	void draw(sf::RenderTarget &target, sf::RenderStates states)const;
	void update(sf::Window &window, float gameTime);
};
#endif