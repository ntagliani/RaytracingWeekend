#include "HittableCollection.h"
#include "HitRecord.h"

HittableCollection::HittableCollection() = default;
HittableCollection::~HittableCollection() = default;

size_t HittableCollection::addHittable(std::unique_ptr<Hittable> hittable)
{
    const auto size = m_collection.size();
    m_collection.emplace_back(std::move(hittable));
    return size;
}

bool HittableCollection::hit(const Ray& r, const Interval& interval,
                             HitRecord* record) const
{
    HitRecord tmp;
    float closest = interval.max;
    bool hit = false;
    for (auto& hittable : m_collection)
    {
        if (hittable->hit(r, Interval(interval.min, closest), &tmp))
        {
            hit = true;
            closest = tmp.m_ray_distance;
            *record = tmp;
        }
    }
    return hit;
}
