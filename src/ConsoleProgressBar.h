#pragma once
#include <string>

#include "Progress.h"

class ConsoleProgressBar : public Progress
{
  public:
    ConsoleProgressBar(std::string title);
    virtual ~ConsoleProgressBar() = default;

    void initialize(const Progression &p) override;
    void update(const Progression &p) override;
    void complete(const Progression &p) override;

  private:
    void displayProgressBar(float percentage) const;

    std::string m_title;
};
