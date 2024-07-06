#pragma once

#include "Hittable.h"

#include <memory>
#include <vector>

class HittableCollection : public Hittable
{
  public:
    HittableCollection();
    ~HittableCollection() override;

    size_t addHittable(std::unique_ptr<Hittable> hittable);
    bool hit(const Ray& r, const Interval& interval,
             HitRecord* record) const override;

  private:
    std::vector<std::unique_ptr<Hittable>> m_collection;
};
