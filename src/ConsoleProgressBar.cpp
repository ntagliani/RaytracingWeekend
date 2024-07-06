#include "ConsoleProgressBar.h"
#include <iomanip>
#include <iostream>

ConsoleProgressBar::ConsoleProgressBar(std::string title)
    : m_title(std::move(title))
{
}

void ConsoleProgressBar::initialize(const Progression& p)
{
    displayProgressBar(p.percentage());
}
void ConsoleProgressBar::update(const Progression& p)
{
    displayProgressBar(p.percentage());
}
void ConsoleProgressBar::complete(const Progression& p)
{
    displayProgressBar(p.percentage());
    std::cout << std::endl;
}

void ConsoleProgressBar::displayProgressBar(float percentage) const
{
    int value = static_cast<int>(percentage * 100);
    std::cout << m_title << " " << std::setw(3) << value << "%\r";
}
