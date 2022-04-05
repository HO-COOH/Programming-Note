#include "factory/Factory.h"

using namespace factory;
int main(int argc, char const* argv[])
{
    auto& factory = Factory::GetFactory(argv[1]);

    auto people = factory.createLink(" 人民日报", "http://www.people.com.cn/");
    auto gmw = factory.createLink(" 光明日报", "http://www.gmw.cn/");

    auto us_yahoo = factory.createLink("Yahoo!", "http://www.yahoo.com/");
    auto jp_yahoo = factory.createLink("Yahoo!Japan", "http://www.yahoo.co.jp/");
    auto excite = factory.createLink("Excite", "http://www.excite.com/");
    auto google = factory.createLink("Google", "http://www.google.com/");

    auto traynews = factory.createTray(" 日报");
    traynews->add(std::move(people));
    traynews->add(std::move(gmw));

    auto traySearch = factory.createTray(" 检索引擎");
    traySearch->add(std::move(us_yahoo));
    traySearch->add(std::move(jp_yahoo));
    traySearch->add(std::move(excite));

    auto page = factory.createPage("LinkPage", "杨文轩 ");
    page->add(std::move(traynews));
    page->add(std::move(traySearch));

    page->output();
}