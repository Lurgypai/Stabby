#pragma once
#include "EntitySystem.h"
#include "AABB.h"
#include "Color.h"
#include <memory>

class StatReader {
	friend class StatBarComponent;
public:
	virtual ~StatReader() = 0 {};
protected:
	StatReader(EntityId target_) : target{ target_ } {};
	virtual float getRatio() = 0;

	virtual StatReader* clone() = 0;

	EntityId target;
};

using StatReaderPtr = std::unique_ptr<StatReader>;

class StatBarComponent {
public:
	StatBarComponent(EntityId id_ = 0);
	StatBarComponent(const StatBarComponent& other);
	StatBarComponent& operator=(const StatBarComponent& other);
	EntityId getId() const;

	template<typename T>
	void setStatReader();

	template<typename T>
	T& getStatReader();

	void update();

	void setTarget(EntityId target_);

	AABB getCurrBarSize() const;

	AABB fullSize;
	bool flipped;
	bool fadeIn;
	Color c;
private:
	StatReaderPtr statReader;
	EntityId target;
	EntityId id;
};

template<typename T>
inline void StatBarComponent::setStatReader() {
	statReader = std::make_unique<T>(target);
}

template<typename T>
inline T& StatBarComponent::getStatReader() {
	return *static_cast<T*>(statReader.get());
}
