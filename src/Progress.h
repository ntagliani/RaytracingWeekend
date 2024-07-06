#pragma once

class Progression
{
  public:
    virtual ~Progression() = default;
    virtual float percentage() const = 0;
};

class Progress
{
  public:
    virtual ~Progress() = default;

    virtual void initialize(const Progression &p) = 0;
    virtual void update(const Progression &p) = 0;
    virtual void complete(const Progression &p) = 0;
};
