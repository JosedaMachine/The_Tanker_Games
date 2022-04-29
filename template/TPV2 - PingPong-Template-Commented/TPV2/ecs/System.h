// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

class Manager;

class System {
public:
	virtual ~System() {
	}

	void setMngr(Manager *mngr) {
		manager_ = mngr;
	}

	virtual void init() {
	}

	virtual void update() {
	}

protected:
	Manager *manager_;
};

