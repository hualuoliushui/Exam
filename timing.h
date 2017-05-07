#ifndef GSS_TIMING_H
#define GSS_TIMING_H
#include <iostream>
#include <stdarg.h>
#include <vector>
#include <time.h>

namespace gss{
	static std::ostream& cout = std::cout;
	

	/*
		对函数的运行进行计时
		计时方式如下：
			Timing timing;
			timing.start();//1
			timing.start();//2
			......
			timing.end();//2
			timing.end();//1
	*/
	class Timing{
	private:
		class ClockNode{
		private:
			unsigned int _index;
			clock_t _clock;
			bool _isSet;
			clock_t _result;
		public:
			ClockNode();
			ClockNode(int index,clock_t clock);

			unsigned int get_index();
			clock_t get_clock();
			clock_t get_result();

			void set_result(clock_t);
			bool isSet();
		};

	    std::vector<ClockNode> _timers;
		unsigned int _timer_size;
		unsigned int _cur_index;

		static char* _name;

	public:
		Timing();
		~Timing();

		/*
			启动计时器，并输出提示语句
		*/
		void start();
		/*
			结束计时器，并输出计时结果
		*/
		void end();
	};

	//==================

	char* Timing::_name = "计时器";

	//******************
	Timing::Timing()
		:_timer_size(0), _cur_index(0){

	}

	Timing::~Timing(){
		for (unsigned int i = 1; i <= _timer_size; ++i)
		{
			if (!_timers.at(i - 1).isSet()){
				cout << "\n" << _name << "(" << _timers.at(i - 1).get_index() << ")丢失\n";
			}
		}
	}

	void Timing::start(){
		_timers.push_back(ClockNode(++_timer_size, clock()));
		++_cur_index;
		gss::cout << "\n" << _name << "(" << _timer_size << ")启动\n";
	}

	void Timing::end(){
		if (_cur_index == 0 || _cur_index > _timer_size)
			return;
		_timers.at(_cur_index - 1).set_result(clock() - _timers.at(_cur_index - 1).get_clock());
		gss::cout << "\n" << _name << "(" << _timer_size << ")---用时" << _timers.at(_cur_index-1).get_result() << "ms\n";
		--_cur_index;
	}


	Timing::ClockNode::ClockNode(){

	}

	Timing::ClockNode::ClockNode(int index, clock_t clock)
		:_index(index), _clock(clock), _result(0), _isSet(false){

	}

	unsigned int Timing::ClockNode::get_index(){
		return _index;
	}

	clock_t Timing::ClockNode::get_clock(){
		return _clock;
	}

	clock_t Timing::ClockNode::get_result(){
		return _result;
	}

	void Timing::ClockNode::set_result(clock_t clock){
		if (!_isSet){
			_isSet = true;
			_result = clock;
		}
	}

	bool Timing::ClockNode::isSet(){
		return _isSet;
	}
}
#endif