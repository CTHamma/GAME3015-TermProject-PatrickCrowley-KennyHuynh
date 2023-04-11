#pragma region step 11
#include "TitleState.hpp"
//#include "Utility.hpp"
#include "ResourceHolder.hpp"


TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
{
	mBackgroundSprite = new SpriteNode(context.window, "MenuBackground");
	mText = new SpriteNode(context.window, "MenuTitle");

	mTextEffectTime = 0.0f;
	mShowText = true;

	//mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

	//mText.setFont(context.fonts->get(Fonts::Main));
	//mText.setString("Press any key to start");
	//centerOrigin(mText);
	//mText.setPosition(context.window->getView().getSize() / 2.f);
}

TitleState::~TitleState()
{
}

void TitleState::draw()
{
	Game& window = *getContext().window;
	mBackgroundSprite->draw();

	//if (mShowText)
	//	window.draw(mText);
}

bool TitleState::update(const GameTimer& dt)
{
	mTextEffectTime += dt.DeltaTime();

	if (mTextEffectTime >= 0.5f)
	{
		mShowText = !mShowText;
		mTextEffectTime = 0.0f;
	}

	return true;
}

bool TitleState::handleEvent()
{
	// If any key is pressed, trigger the next screen
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		requestStackPop();
		requestStackPush(States::Menu);
	}

	return true;
}
void TitleState::buildScene()
{
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mContext.window, "MenuBackground"));

	mBackgroundSprite = backgroundSprite.get();
	mBackgroundSprite->setPosition(0.0f, 0.0f, 0.0f);
	mBackgroundSprite->setWorldRotation(0.0f, 0.0f, 0.0f);
}
#pragma endregion
