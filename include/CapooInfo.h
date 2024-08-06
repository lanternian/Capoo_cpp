#ifndef CAPOOINFO_H
#define CAPOOINFO_H

#include <iostream>
#include <fstream>
#include <string>
#include <json/json.h>

const std::string KET[] = {
    "id",
    "name",
    "collider_Adjust",
    "body",
    "body_Anim",
    "handIndex",
    "face",
    "face_Anim",
    "face_decoration",
    "face_decoration_Anim",
    "hat",
    "hat_Anim",
    "clothes",
    "clothes_Anim",
    "back",
    "back_hierarchy",
    "back_Anim",
    "right_hand_item",
    "right_hand_item_Anim",
    "capoo_acc_top",
    "capoo_acc_top_Anim",
    "capoo_acc_body",
    "capoo_acc_body_Anim",
    "capoo_acc_bot",
    "capoo_acc_bot_Anim",
    "mood",
    "mood_Anim",
    "efx_bot",
    "efx_bot_Anim",
    "efx_top",
    "efx_top_Anim",
    "efx_appears",
    "efx_appears_Anim",
    "talk",
    "talk_Anim",
    "food",
    "food_Anim",
    "poo",
    "poo_Anim"
};

class CapooInfo
{
public:
    CapooInfo(const CapooInfo&) = delete;
    CapooInfo& operator=(const CapooInfo&) = delete;
	static CapooInfo &getInstance()
	{
		static CapooInfo instance;
		return instance;
	}
    Json::Value getID(int id) const;
    Json::Value getID(std::string id) const;
    void printInfo(int id) const;
    void printInfo(std::string id) const;
private:
    CapooInfo();
    ~CapooInfo();
    Json::Value root;
};

#endif