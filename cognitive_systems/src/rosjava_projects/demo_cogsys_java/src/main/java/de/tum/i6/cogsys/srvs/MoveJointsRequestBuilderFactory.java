package de.tum.i6.cogsys.srvs;

import org.ros.exception.RemoteException;
import org.ros.exception.ServiceNotFoundException;
import org.ros.node.ConnectedNode;
import org.ros.node.service.ServiceClient;
import org.ros.node.service.ServiceResponseListener;
import org.smerobotics.util.srv.ServiceRequestBuilderFactory;

import robot_control_srvs.MoveJoints;
import robot_control_srvs.MoveJointsRequest;
import robot_control_srvs.MoveJointsResponse;

public abstract class MoveJointsRequestBuilderFactory extends ServiceRequestBuilderFactory {

	public final String SERVICE_NAME_MOVE_JOINTS = getServiceName();
	
	private ServiceClient<MoveJointsRequest, MoveJointsResponse> clientMoveJoints;

	private final Object sync = new Object();
	private volatile boolean responsePending = false;

	private boolean ok = false;
	
	public abstract String getServiceName();
	
	@Override
	public synchronized void addServiceClients(ConnectedNode connectedNode) {

		if (clientMoveJoints == null) {

			boolean found = false;

			while (!found) {

				try {

					clientMoveJoints = connectedNode.newServiceClient(
							SERVICE_NAME_MOVE_JOINTS,
							MoveJoints._TYPE);

					found = true;

					System.out.println("    Found service '"
							+ SERVICE_NAME_MOVE_JOINTS
							+ "'. (type: "
							+ MoveJoints._TYPE + ")");

				} catch (ServiceNotFoundException e) {

					System.out.println("  Waiting for service '"
							+ SERVICE_NAME_MOVE_JOINTS
							+ "' to start up. (type: "
							+ MoveJoints._TYPE + ")");

					try {
						Thread.sleep(3000);
					} catch (InterruptedException ie) {
					}

				}

			}

		}

	}

	@Override
	public synchronized void removeServiceClients() {

		if (clientMoveJoints != null) {

			clientMoveJoints.shutdown();
			clientMoveJoints = null;

			System.out.println("  Shutdown service client '"
					+ SERVICE_NAME_MOVE_JOINTS
					+ "'. (type: "
					+ MoveJoints._TYPE + ")");

		}

	}

	public boolean call(float q0, float q1, float q2) {

		boolean success = false;

		MoveJointsRequest req = clientMoveJoints.newMessage();
		req.setQ0(q0);
		req.setQ1(q1);
		req.setQ2(q2);

		synchronized (sync) {

			responsePending = true;

			clientMoveJoints.call(req, new ServiceResponseListener<MoveJointsResponse>() {

				@Override
				public void onSuccess(MoveJointsResponse response) {

					synchronized (sync) {
						ok = response.getSuccess();
						responsePending = false;
						sync.notifyAll();
					}

				}

				@Override
				public void onFailure(RemoteException e) {

					synchronized (sync) {
						ok = false;
						responsePending = false;
						sync.notifyAll();
					}

				}

			});

			while (responsePending) {
				try {
					sync.wait();
				} catch (InterruptedException e1) {
				}
			}

			success = ok;

		}

		return success;

	}

}
