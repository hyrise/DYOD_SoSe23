#include "storage_manager.hpp"

#include "utils/assert.hpp"

namespace opossum {

StorageManager& StorageManager::get() {
  static StorageManager instance; 
  return instance; 
}

void StorageManager::add_table(const std::string& name, std::shared_ptr<Table> table) {
  _tables[name] = table; 
}

void StorageManager::drop_table(const std::string& name) {
  std::map<std::string,std::shared_ptr<Table>>::iterator iter = _tables.find(name);
  if(iter == _tables.end()){
    throw std::logic_error("Table does not exist.");
  } else {
    _tables.erase(iter);
  }
}

std::shared_ptr<Table> StorageManager::get_table(const std::string& name) const {
  auto iter = _tables.find(name);
  if(iter != _tables.end()){
    return _tables.at(name);
  }
  throw std::logic_error("...");
}

bool StorageManager::has_table(const std::string& name) const {
  auto iter = _tables.find(name);
  return iter != _tables.end();
}

std::vector<std::string> StorageManager::table_names() const {
  std::vector<std::string> table_names; 
  for(auto [key, value] : _tables){
    table_names.push_back(key);
  }
  return table_names;
}

void StorageManager::print(std::ostream& out) const {
  for(auto [key, value] : _tables){
    std::cout << key << " #columns: " << value->column_count() << " #rows: " << value->row_count() << " #chunks " << value->chunk_count() << std::endl; 
  }
}

void StorageManager::reset() {
  _tables.clear(); 
}

}  // namespace opossum
