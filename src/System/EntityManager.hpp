#pragma once
#include <functional>
#include <string>
#include <typeindex>
#include <unordered_map>

class EntityProp 
{
public:
  EntityProp(std::type_index id)
    :_id(id) { }

  std::type_index Id() const {
    return _id;
  }

  template<typename T>
  bool Is() {
    return std::type_index(typeid(T)) == _id;
  }

  template<typename T>
  T* As() {
    if (!Is<T>()) {
      throw std::runtime_error("Invalid type");
    }

    return static_cast<T*>(this);
  }

private:
  std::type_index _id;
};

template <typename T>
class EntityPrimitive : public EntityProp {
public:
  EntityPrimitive(std::function<T()> getFn, std::function<void(const T&)> setFn)
    :EntityProp(std::type_index(typeid(*this))),
    _getFn(getFn),
    _setFn(setFn) {

  }

  void Set(const T& value) {
    _setFn(value);
  }

  T Get() const {
    return _getFn();
  }

private:
  std::function<T()> _getFn;
  std::function<void(const T&)> _setFn;
};

class EntityPropContainer : public EntityProp {
public:
  EntityPropContainer()
    :EntityProp(std::type_index(typeid(*this))) { }

  template <typename T>
  void Publish(const std::string& id, std::function<T()> getFn, std::function<void(T)> setFn) {
    _lookup[id] = std::make_shared<EntityPrimitive<T>>(getFn, setFn);
  }

  template<typename T>
  T& Get(const std::string& id) {
    return _lookup.at(id)->As<EntityPrimitive<T>>()->Get();
  }

  template<typename T>
  void Set(const std::string& id, T& value) {
    _lookup.at(id)->As<EntityPrimitive<T>>()->Set(value);
  }

private:
  std::unordered_map<std::string, std::shared_ptr<EntityProp>> _lookup;
};

class EntityManager
{
public:
  using Ptr = std::shared_ptr<EntityManager>;

  EntityManager();
	~EntityManager();
  
  template <typename T>
  void Publish(const std::string& id, std::function<T()> getFn, std::function<void(T)> setFn) {
    _lookup[id] = std::make_shared<EntityPrimitive<T>>(getFn, setFn);
  }

  void Publish(const std::string& id, std::shared_ptr<EntityPropContainer> container) {
    _lookup[id] = container;
  }

  EntityProp& Request(const std::string& id) {
    return *_lookup.at(id);
  }

private:
  std::unordered_map<std::string, std::shared_ptr<EntityProp>> _lookup;
};
