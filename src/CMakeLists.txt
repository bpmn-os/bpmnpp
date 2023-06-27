include("${SOURCE_DIR}/xml/bpmn/CMakeLists.txt")

list(TRANSFORM bpmn_HEADERS PREPEND "xml/")
list(TRANSFORM bpmn_SOURCES PREPEND "xml/")

list(PREPEND bpmn_SOURCES
  xml/XMLObject.cpp
)

list(APPEND bpmn_SOURCES
  SequenceFlow.cpp
  Node.cpp
  BoundaryEvent.cpp
  Model.cpp
)

list(PREPEND bpmn_HEADERS
  xml/XMLObject.h
)

list(APPEND bpmn_HEADERS
  SequenceFlow.h
  Node.h
  BoundaryEvent.h
  Model.h
)
