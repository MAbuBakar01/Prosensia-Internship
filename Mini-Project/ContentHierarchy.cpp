#include "ContentHierarchy.h"

//========================================Topic Class Implementations================================
Topic::Topic() {}
Topic::Topic(std::string id, std::string cId, std::string t, std::string desc)
    : topicId(id), courseId(cId), title(t), description(desc) {}

// Getters
std::string Topic::getTopicId() const { return topicId; }
std::string Topic::getCourseId() const { return courseId; }
std::string Topic::getTitle() const { return title; }
std::string Topic::getDescription() const { return description; }

// Setters
void Topic::setTopicId(const std::string& id) { topicId = id; }
void Topic::setCourseId(const std::string& cId) { courseId = cId; }
void Topic::setTitle(const std::string& t) { title = t; }
void Topic::setDescription(const std::string& desc) { description = desc; }

//========================================SubTopic Class Implementations================================
SubTopic::SubTopic() {}
SubTopic::SubTopic(std::string id, std::string tId, std::string t, std::string desc)
    : subTopicId(id), topicId(tId), title(t), description(desc) {}

// Getters
std::string SubTopic::getSubTopicId() const { return subTopicId; }
std::string SubTopic::getTopicId() const { return topicId; }
std::string SubTopic::getTitle() const { return title; }
std::string SubTopic::getDescription() const { return description; }

// Setters
void SubTopic::setSubTopicId(const std::string& id) { subTopicId = id; }
void SubTopic::setTopicId(const std::string& tId) { topicId = tId; }
void SubTopic::setTitle(const std::string& t) { title = t; }
void SubTopic::setDescription(const std::string& desc) { description = desc; }

//========================================Lesson Class Implementations================================
Lesson::Lesson() {}
Lesson::Lesson(std::string id, std::string stId, std::string c)
    : lessonId(id), subTopicId(stId), content(c) {}

// Getters
std::string Lesson::getLessonId() const { return lessonId; }
std::string Lesson::getSubTopicId() const { return subTopicId; }
std::string Lesson::getContent() const { return content; }

// Setters
void Lesson::setLessonId(const std::string& id) { lessonId = id; }
void Lesson::setSubTopicId(const std::string& stId) { subTopicId = stId; }
void Lesson::setContent(const std::string& c) { content = c; }
