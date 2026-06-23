(function () {
  const root = document.documentElement;
  const key = "dm9051-doc-theme";
  const button = document.getElementById("themeToggle");

  function applyTheme(theme) {
    root.setAttribute("data-theme", theme);
    const icon = theme === "dark" ? "🌙" : "☀";
    const label = theme === "dark" ? "Dark" : "Light";
    if (button) {
      button.textContent = `${icon} ${label}`;
    }
  }

  const saved = localStorage.getItem(key);
  const initial = saved || "light";
  applyTheme(initial);

  if (button) {
    button.addEventListener("click", function () {
      const next = root.getAttribute("data-theme") === "dark" ? "light" : "dark";
      applyTheme(next);
      localStorage.setItem(key, next);
    });
  }
})();
