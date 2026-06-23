(function () {
  function slugify(text) {
    return text
      .trim()
      .toLowerCase()
      .replace(/[\s\/()]+/g, "-")
      .replace(/[^\w\-\u4e00-\u9fff]+/g, "")
      .replace(/-+/g, "-")
      .replace(/^-|-$/g, "");
  }

  function buildToc(containerId, tocId) {
    const container = document.getElementById(containerId);
    const toc = document.getElementById(tocId);
    if (!container || !toc) {
      return;
    }

    const headings = container.querySelectorAll("h1, h2, h3, h4");
    toc.innerHTML = "";

    headings.forEach((h) => {
      if (!h.id) {
        h.id = slugify(h.textContent);
      }
      const level = Number(h.tagName.replace("H", ""));
      const a = document.createElement("a");
      a.href = `#${h.id}`;
      a.textContent = h.textContent;
      a.className = `nav-link toc-level-${level}`;

      a.addEventListener("click", function (e) {
        e.preventDefault();
        document.getElementById(h.id).scrollIntoView({ behavior: "smooth", block: "start" });
        const offcanvasEl = document.getElementById("mobileSidebar");
        if (offcanvasEl && window.bootstrap) {
          const inst = bootstrap.Offcanvas.getInstance(offcanvasEl);
          if (inst) {
            inst.hide();
          }
        }
      });

      toc.appendChild(a);
    });

    const observer = new IntersectionObserver(
      (entries) => {
        entries.forEach((entry) => {
          const id = entry.target.getAttribute("id");
          const link = toc.querySelector(`a[href="#${id}"]`);
          if (!link) return;
          if (entry.isIntersecting) {
            toc.querySelectorAll(".nav-link.active").forEach((el) => el.classList.remove("active"));
            link.classList.add("active");
          }
        });
      },
      { rootMargin: "-35% 0px -55% 0px", threshold: 0.01 }
    );

    headings.forEach((h) => observer.observe(h));
  }

  function buildFigureList() {
    const list = document.getElementById("figureNav");
    if (!list) return;
    list.innerHTML = "";

    document.querySelectorAll(".figure-card").forEach((fig) => {
      const id = fig.id;
      const title = fig.querySelector("h5")?.textContent || id;
      const a = document.createElement("a");
      a.className = "nav-link";
      a.href = `#${id}`;
      a.textContent = title;
      list.appendChild(a);
    });
  }

  function initCodeBlocks() {
    document.querySelectorAll("pre code").forEach((code) => {
      if (window.hljs) {
        window.hljs.highlightElement(code);
      }
      const pre = code.closest("pre");
      if (!pre || pre.querySelector(".copy-btn")) {
        return;
      }
      const btn = document.createElement("button");
      btn.className = "copy-btn";
      btn.type = "button";
      btn.textContent = "Copy";
      btn.addEventListener("click", async function () {
        try {
          await navigator.clipboard.writeText(code.textContent || "");
          btn.textContent = "Copied";
          setTimeout(() => {
            btn.textContent = "Copy";
          }, 1200);
        } catch (_) {
          btn.textContent = "Fail";
        }
      });
      pre.appendChild(btn);
    });
  }

  document.addEventListener("DOMContentLoaded", function () {
    buildToc("doc-content", "tocNav");
    buildFigureList();
    initCodeBlocks();

    const mobileToc = document.getElementById("mobileTocNav");
    const desktopToc = document.getElementById("tocNav");
    if (mobileToc && desktopToc) {
      mobileToc.innerHTML = desktopToc.innerHTML;
      mobileToc.querySelectorAll("a").forEach((a) => {
        a.addEventListener("click", function (e) {
          e.preventDefault();
          const target = document.querySelector(a.getAttribute("href"));
          if (target) {
            target.scrollIntoView({ behavior: "smooth", block: "start" });
          }
          if (window.bootstrap) {
            const pane = document.getElementById("mobileSidebar");
            const inst = bootstrap.Offcanvas.getInstance(pane);
            if (inst) inst.hide();
          }
        });
      });
    }
  });
})();
