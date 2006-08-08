bool RasterSettingsWindow::Event(EventInfo &info) {
  switch(info.event_id) {

  case EVENT_CHANGED: {
    if(info.control == &PScanlineSlider) {
      config::video.pscanline_intensity = PScanlineSlider.GetPos();
      PScanlineLabel.SetText("Progressive: %d%%", uint(config::video.pscanline_intensity));
      uiVideo->update_scanlines();
    } else if(info.control == &IScanlineSlider) {
      config::video.iscanline_intensity = IScanlineSlider.GetPos();
      IScanlineLabel.SetText("Interlace: %d%%", uint(config::video.iscanline_intensity));
      uiVideo->update_scanlines();
    }
  } break;

  }

  return false;
}

void RasterSettingsWindow::Setup() {
  Header.Create(this, "visible", 0, 0, 475, 30, "Raster Settings");
  Header.SetFont(global::font_header);

int x = 15, y = 30;
  ScanlineLabel.Create(this, "visible", x, y, 460, 15,
    "Scanline intensity adjust: (0% = no scanlines, 100% = full scanlines)");
  y += 20;

  PScanlineLabel.Create(this, "visible", x, y, 100, 15);
  PScanlineLabel.SetText("Progressive: %d%%", uint(config::video.pscanline_intensity));
  PScanlineSlider.Create(this, "visible", x + 105, y - 3, 355, 25);
  PScanlineSlider.SetRange(0, 100);
  PScanlineSlider.SetPos(config::video.pscanline_intensity);
  y += 25;

  IScanlineLabel.Create(this, "visible", x, y, 100, 15);
  IScanlineLabel.SetText("Interlace: %d%%", uint(config::video.iscanline_intensity));
  IScanlineSlider.Create(this, "visible", x + 105, y - 3, 355, 25);
  IScanlineSlider.SetRange(0, 100);
  IScanlineSlider.SetPos(config::video.iscanline_intensity);
  y += 25;
}