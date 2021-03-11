#include "content.h"

Content::Content(QWidget *parent)
	: QFrame(parent)
{
	stack = new QStackedWidget(parent);
	stack->setFrameStyle(QFrame::Panel | QFrame::Raised);

	ep = new EncodePage();
	dp = new DecodePage();

	stack->addWidget(ep);
	stack->addWidget(dp);
	stack->setMinimumWidth(458);
}

Content::~Content()
{

}
