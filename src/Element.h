#ifndef BPMN_Element_H
#define BPMN_Element_H

#include "xml/bpmn/tBaseElement.h"

namespace BPMN {

/**
 * @brief Abstract base class for all elements in a BPMN model.
 *
 * The class provides conveniance methods to cast the element to concrete types.
 */
class Element {
public:
  virtual ~Element() = default;

  /**
   * @brief Attempts to cast the element to the specified type T.
   * @return A pointer to casted object or `nullptr` if the cast fails
   */
  template<typename T> T* represents() {
    return dynamic_cast<T*>(this);
  }

  /**
   * @brief Attempts to cast the element to the specified type T.
   * @return A pointer to casted object or `nullptr` if the cast fails
   */
  template<typename T> const T* represents() const {
    return dynamic_cast<const T*>(this);
  }

  /**
   * @brief Casts the element to the specified type T.
   * @return A pointer to casted object
   * @throws std::runtime_error if cast fails
   */
  template<typename T> T* as() {
    T* ptr = dynamic_cast<T*>(this);
    if ( ptr == nullptr ) {
      throw std::runtime_error("Element: Illegal cast of element");
    }
    return ptr;
  }

  /**
   * @brief Casts the element to the specified type  T.
   * @return A pointer to casted object
   * @throws std::runtime_error if cast fails
   */
  template<typename T> const T* as() const {
    const T* ptr = dynamic_cast<const T*>(this);
    if ( ptr == nullptr ) {
      throw std::runtime_error("Element: Illegal cast of element");
    }
    return ptr;
  }
};

} // namespace BPMN

#endif // BPMN_Element_H
