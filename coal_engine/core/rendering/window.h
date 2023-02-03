#pragma once

#include "core/base.h"
#include "core/events/event.h"
#include <GLFW/glfw3.h>

namespace engine {
	class Window {
		public:
		using EventCallbackFunc = std::function<void(Event&)>;
		static const int min_width, min_height;

		Window(const std::string title);
		~Window();

		void init();

		void set_event_callback(const EventCallbackFunc& callback) { _data.event_callback = callback; }

		void set_width(int width);
		void set_height(int height);
		void set_fullscreen(bool fullscreen);
		void set_vsync(bool enabled);

		inline const std::string& get_title() const& { return _data.title; }
		inline int get_width() const { return _data.width; }
		inline int get_height() const { return _data.height; }
		inline bool get_fullscreen() const { return _data.fullscreen; }
		inline bool get_vsync() const { return _data.vsync; }
		inline bool is_minimized() const { return _data.minimized; }
		GLFWwindow* get_ptr() const { return _ptr; }

		void swap_buffers();
		void poll_events();
		bool should_close();
		private:
		GLFWwindow* _ptr;
		int start_y; // Used to prevent window widgets from going off-screen

		struct WindowData {
			std::string title;
			int width = 0, height = 0;
			bool fullscreen = false, vsync = true;
			bool minimized = false;

			EventCallbackFunc event_callback;
		};
		WindowData _data;
	};
}
