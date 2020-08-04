#ifndef APPLICATION_WINDOW_HPP
#define APPLICATION_WINDOW_HPP

#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/headerbar.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <gtkmm/menubutton.h>
#include <gtkmm/popover.h>
#include <gtkmm/stack.h>
#include <gtkmm/togglebutton.h>
#include "application.hpp"
#include "calibration_ui.hpp"
#include "presets_menu_ui.hpp"
#include "pulse_info_ui.hpp"
#include "sink_input_effects_ui.hpp"
#include "source_output_effects_ui.hpp"

class ApplicationUi : public Gtk::ApplicationWindow {
 public:
  ApplicationUi(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder, Application* application);
  ApplicationUi(const ApplicationUi&) = delete;
  auto operator=(const ApplicationUi&) -> ApplicationUi& = delete;
  ApplicationUi(const ApplicationUi&&) = delete;
  auto operator=(const ApplicationUi &&) -> ApplicationUi& = delete;
  ~ApplicationUi() override;

  static auto create(Application* app) -> ApplicationUi*;

 private:
  std::string log_tag = "application_ui: ";

  Application* app;

  Glib::RefPtr<Gio::Settings> settings;

  Gtk::Button *calibration_button = nullptr, *help_button = nullptr;
  Gtk::ToggleButton* bypass_button = nullptr;
  Gtk::Stack *stack = nullptr, *stack_menu_settings = nullptr;
  Gtk::Label* headerbar_info = nullptr;
  Gtk::Popover* presets_menu = nullptr;
  Gtk::MenuButton* presets_menu_button = nullptr;
  Gtk::Label* presets_menu_label = nullptr;

  Gtk::Grid* subtitle_grid = nullptr;
  Gtk::HeaderBar* headerbar = nullptr;
  Gtk::Image *headerbar_icon1 = nullptr, *headerbar_icon2 = nullptr;

  std::vector<sigc::connection> connections;

  PresetsMenuUi* presets_menu_ui = nullptr;

  SinkInputEffectsUi* sie_ui = nullptr;
  SourceOutputEffectsUi* soe_ui = nullptr;
  PulseInfoUi* pulse_info_ui = nullptr;

  int sie_latency = 0, soe_latency = 0;

  static void get_object(const Glib::RefPtr<Gtk::Builder>& builder,
                         const std::string& name,
                         Glib::RefPtr<Gtk::Adjustment>& object) {
    object = Glib::RefPtr<Gtk::Adjustment>::cast_dynamic(builder->get_object(name));
  }

  void update_headerbar_subtitle(const int& index);

  static void apply_css_style(const std::string& css_file_name);

  void on_stack_visible_child_changed();

  void on_calibration_button_clicked();
};

#endif