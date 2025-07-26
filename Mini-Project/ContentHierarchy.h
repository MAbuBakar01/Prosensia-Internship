#ifndef CONTENTHIERARCHY_H
#define CONTENTHIERARCHY_H

#include <string>

//========================================Topic Class================================
class Topic {
private:
    std::string topicId;
    std::string courseId; // Link to parent Course
    std::string title;
    std::string description;
public:
    Topic();
    Topic(std::string id, std::string cId, std::string t, std::string desc);

    // Getters
    std::string getTopicId() const;
    std::string getCourseId() const;
    std::string getTitle() const;
    std::string getDescription() const;

    // Setters
    void setTopicId(const std::string& id);
    void setCourseId(const std::string& cId);
    void setTitle(const std::string& t);
    void setDescription(const std::string& desc);
};

//========================================SubTopic Class================================
class SubTopic {
private:
    std::string subTopicId;
    std::string topicId; // Link to parent Topic
    std::string title;
    std::string description;
public:
    SubTopic();
    SubTopic(std::string id, std::string tId, std::string t, std::string desc);

    // Getters
    std::string getSubTopicId() const;
    std::string getTopicId() const;
    std::string getTitle() const;
    std::string getDescription() const;

    // Setters
    void setSubTopicId(const std::string& id);
    void setTopicId(const std::string& tId);
    void setTitle(const std::string& t);
    void setDescription(const std::string& desc);
};

//========================================Lesson Class================================
class Lesson {
private:
    std::string lessonId;
    std::string subTopicId; // Link to parent SubTopic
    std::string content;
public:
    Lesson();
    Lesson(std::string id, std::string stId, std::string c);

    // Getters
    std::string getLessonId() const;
    std::string getSubTopicId() const;
    std::string getContent() const;

    // Setters
    void setLessonId(const std::string& id);
    void setSubTopicId(const std::string& stId);
    void setContent(const std::string& c);
};

#endif // CONTENTHIERARCHY_H
