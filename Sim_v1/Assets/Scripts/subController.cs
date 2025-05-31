using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class subController : MonoBehaviour
{
    public float SCA;
    public float maxFS;
    public float maxBS;
    public float minSpeed;
    public float turnSpeed;
    public float riseSpeed;
    public float stabSmooth;

    private float curSpeed;
    private Rigidbody rb;

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        if (Input.GetKey(KeyCode.W)) {
            curSpeed += SCA;
        }
        else if (Input.GetKey(KeyCode.S)) {
            curSpeed -= SCA;
        }
        else if (Mathf.Abs(curSpeed) <= minSpeed) {
            curSpeed = 0;
        }
        curSpeed = Mathf.Clamp(curSpeed, -maxBS, maxFS);
        rb.AddForce(transform.forward * curSpeed);

        if (Input.GetKey(KeyCode.D)) {
            rb.AddTorque(transform.up * turnSpeed);
        }
        else if (Input.GetKey(KeyCode.A)) {
            rb.AddTorque(transform.up * -turnSpeed);
        }

        if (Input.GetKey(KeyCode.LeftShift)) {
            rb.AddForce(transform.up * riseSpeed);
        }
        else if (Input.GetKey(KeyCode.LeftControl)) {
            rb.AddForce(transform.up * -riseSpeed);
        }

        rb.MoveRotation(Quaternion.Slerp(rb.rotation, Quaternion.Euler(new Vector3(0, rb.rotation.eulerAngles.y, 0)), stabSmooth));
    }
}
