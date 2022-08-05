// @ts-check
// Note: type annotations allow type checking and IDEs autocompletion

const lightCodeTheme = require("prism-react-renderer/themes/github");
const darkCodeTheme = require("prism-react-renderer/themes/dracula");

/** @type {import('@docusaurus/types').Config} */
const config = {
  title: "Learn C | by Birnadin E. 🤗",
  tagline: "A self-guide and a personal reference",
  url: "https://learnc.birnadine.guru",
  baseUrl: "/",
  onBrokenLinks: "throw",
  onBrokenMarkdownLinks: "warn",
  favicon: "img/favicon.ico",
  organizationName: "BirnadinErick",
  projectName: "learn-c",
  i18n: {
    defaultLocale: "en",
    locales: ["en"],
  },
  presets: [
    [
      "classic",
      /** @type {import('@docusaurus/preset-classic').Options} */
      ({
        docs: {
          sidebarPath: require.resolve("./sidebars.js"),
        },
        blog: {
          showReadingTime: true,
        },
        theme: {
          customCss: require.resolve("./src/css/custom.css"),
        },
      }),
    ],
  ],

  themeConfig:
    /** @type {import('@docusaurus/preset-classic').ThemeConfig} */
    ({
      navbar: {
        title: "Learn C",
        logo: {
          alt: "C logo",
          src: "img/favicon-32x32.png",
        },
        items: [
          {
            type: "doc",
            docId: "intro",
            position: "left",
            label: "Concepts",
          },
          { to: "/blog", label: "Assignments", position: "left" },
          {
            href: "https://github.com/BirnadinErick/learn-c.git",
            label: "Source",
            position: "right",
          },
        ],
      },
      footer: {
        style: "dark",
        links: [
          {
            title: "Concepts",
            items: [
              {
                label: "Development Environment",
                to: "/docs/intro",
              },
            ],
          },
          {
            title: "Assignments",
            items: [
              {
                label: "Intro",
                to: "/blog",
              },
            ],
          },
          {
            title: "Let's Socialize 🤗",
            items: [
              {
                label: "Stack Overflow",
                href: "https://stackoverflow.com/users/12621898/birnadin-erick",
              },
              {
                label: "Medium",
                href: "https://medium.com/@birnadine",
              },
              {
                label: "Twitter",
                href: "https://twitter.com/birnadin_e",
              },
              {
                label: "GitHub",
                href: "https://github.com/BirnadinErick",
              },
            ],
          },
        ],
        copyright: `Copyright © ${new Date().getFullYear()} Birnadin Erick. 👨‍💻 with 💖 from Jaffna`,
      },
      prism: {
        theme: lightCodeTheme,
        darkTheme: darkCodeTheme,
      },
    }),
};

module.exports = config;
