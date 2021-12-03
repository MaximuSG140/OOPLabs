#pragma once
#include <deque>
#include <set>

#include "MessageWrapper.h"
#include "Robot.h"

enum class Attribute{UNBREAKABLE, HEAVY};

struct RadioMessage;
class ScaleMap;
class Message;

class SmartRobot :
	public Robot
{
public:
	explicit SmartRobot(std::deque<MessageWrapper>& radio_messages,
		std::set<Attribute> attributes = std::set<Attribute>());
	explicit SmartRobot(std::deque<MessageWrapper>& radio_messages,
		const SmartRobot* master,
		Position place,
		std::set<Attribute> attributes = std::set<Attribute>());

	void UpdateMap(const ScaleMap& updated_map);
	void SendMessage(Message* msg);
	void ReceiveMessage(const MessageWrapper& msg);
	void Activate();
	void Deactivate();
	virtual std::string GetRole() = 0;

	virtual EnvironmentQueryWrapper Push(Direction push_direction);
	bool IsActive()const;
	bool HasAttribute(Attribute a)const;
	Position GetPosition()const;
	ScaleMap GetMap() const;
	const SmartRobot* GetMasterId()const;
protected:
	void Move(Direction move_direction) override;
private:
	std::deque<MessageWrapper>& radio_;
	Position place_;
	ScaleMap map_;
	std::set<Attribute> attributes_;
	const SmartRobot* master_;
	bool is_active_;
};

