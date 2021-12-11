#pragma once
class SmartRobot;
class Message;

struct RadioMessage
{
	SmartRobot* sender;
	Message* msg;
};