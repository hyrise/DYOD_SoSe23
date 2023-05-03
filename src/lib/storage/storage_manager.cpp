#include "storage_manager.hpp"

#include "utils/assert.hpp"

namespace opossum {

StorageManager& StorageManager::get() {
  static StorageManager instance;
  return instance;
}

void StorageManager::add_table(const std::string& name, std::shared_ptr<Table> table) {
  if (has_table(name)) {
    throw std::logic_error("Table already exists.");
  } else {
    _tables[name] = table;
  }
}

void StorageManager::drop_table(const std::string& name) {
  if (has_table(name)) {
    _tables.erase(_tables.find(name));
  } else {
    throw std::logic_error("Table does not exist.");
  }
}

std::shared_ptr<Table> StorageManager::get_table(const std::string& name) const {
  if (has_table(name)) {
    return _tables.at(name);
  } else {
    throw std::logic_error("Table does not exist");
  }
}

bool StorageManager::has_table(const std::string& name) const {
  return _tables.find(name) != _tables.end();
}

std::vector<std::string> StorageManager::table_names() const {
  std::vector<std::string> table_names;
  for (auto [key, value] : _tables) {
    table_names.push_back(key);
  }
  return table_names;
}

void StorageManager::print(std::ostream& out) const {
  for (auto [key, value] : _tables) {
    out << key << " #columns: " << value->column_count() << " #rows: " << value->row_count() << " #chunks "
              << value->chunk_count() << std::endl;
  }
}

void StorageManager::reset() {
  _tables.clear();
}

}  // namespace opossum
