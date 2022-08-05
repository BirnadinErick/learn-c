import React from "react";
import clsx from "clsx";
import styles from "./styles.module.css";

const FeatureList = [
  {
    title: "A Self Guide",
    description: (
      <>
        Indented to be used for myself, but useful for others also. Flow follows
        a pattern to guide reader in a progressive way
      </>
    ),
  },
  {
    title: "A Reference",
    description: (
      <>
        Can be used as a reference when coding C or setting up C dev environment
      </>
    ),
  },
  {
    title: "Effective",
    description: (
      <>
        A concept is introduced and then a project is given to make sure reader
        grasped the material
      </>
    ),
  },
];

function Feature({ title, description }) {
  return (
    <div className={clsx("col col--4")}>
      <div className="text--center padding-horiz--md ">
        <h3>{title}</h3>
        <p>{description}</p>
      </div>
    </div>
  );
}

export default function HomepageFeatures() {
  return (
    <section className={styles.features}>
      <div className="container">
        <div className="row">
          {FeatureList.map((props, idx) => (
            <Feature key={idx} {...props} />
          ))}
        </div>
      </div>
    </section>
  );
}
